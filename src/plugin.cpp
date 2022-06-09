#include "plugin.hpp"
#include <gtkmm.h>
#include "joystick.hpp"
#include "main_window.hpp"

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <thread>

#include "mupen64plus/m64p_types.h"
#include "mupen64plus/m64p_vcr.h"
#include "osal_dl.hpp"
#include <resources/css/main.css.rsrc.hpp>

namespace {
  using debug_callback_t = void(void* data, int level, const char* msg);

  const char plugin_name[] = "TASInput2 v1.99.0";

  std::atomic<bool> init_flag;
  debug_callback_t* mupen_debug;
  void* debug_context;

  Glib::RefPtr<Gtk::Application> gtk_app;
  std::optional<std::thread> gtk_thread;

  template <std::derived_from<Gtk::Window> T>
  T& get_main_window() {
    return *static_cast<T*>(gtk_app->get_run_window());
  }

  ptr_VCR_IsPlaying _VCR_IsPlaying;
  ptr_VCR_GetKeys _VCR_GetKeys;
}  // namespace
namespace tasdi2 {
  void debug_log(int log_level, const char* out) {
    if (!init_flag) {
      throw std::runtime_error("Cannot call debug() before plugin initializes");
    }
    mupen_debug(debug_context, log_level, out);
  }
}  // namespace tasdi2

extern "C" {
// CORE PLUGIN API
// ===============
M64P_EXPORT m64p_error M64P_CALL PluginStartup(
  m64p_dynlib_handle dll, void* data, debug_callback_t* debug_callback) {
  mupen_debug   = debug_callback;
  debug_context = data;
  // Start up GTK
  gtk_app = Gtk::Application::create("io.github.jgcodes2020.tasdi2");
  gtk_app->signal_activate().connect([]() {
    { tasdi2::Joystick(); }

    auto css_loader = Gtk::CssProvider::create();
    css_loader->load_from_data(tasdi2::rsrc::css_data);

    auto display = Gdk::Display::get_default();

    Gtk::StyleContext::add_provider_for_display(
      display, css_loader, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  });

  // Check if this core supports VCR
  _VCR_IsPlaying =
    reinterpret_cast<ptr_VCR_IsPlaying>(osal_dlsym(dll, "VCR_IsPlaying"));
  _VCR_GetKeys =
    reinterpret_cast<ptr_VCR_GetKeys>(osal_dlsym(dll, "VCR_GetKeys"));

  init_flag = true;
  return M64ERR_SUCCESS;
}
M64P_EXPORT m64p_error M64P_CALL PluginShutdown() {
  // Shut down GTK
  gtk_app.reset();

  init_flag = false;
  return M64ERR_SUCCESS;
}
M64P_EXPORT m64p_error M64P_CALL PluginGetVersion(
  m64p_plugin_type* type, int* version, int* api_version,
  const char** plugin_name, int* caps) {
  // Input plugin
  if (type != nullptr)
    *type = M64PLUGIN_INPUT;
  // version 1.99.0
  if (version != nullptr)
    *version = 0x00016300;
  // API version 2.1.0
  if (api_version != nullptr)
    *api_version = 0x020100;
  // Plugin: TASInput2 v1.99.0
  if (plugin_name != nullptr)
    *plugin_name = &::plugin_name[0];
  // caps not defined for plugins
  if (caps != nullptr)
    *caps = 0;
  return M64ERR_SUCCESS;
}

M64P_EXPORT int M64P_CALL RomOpen() {
  // Init GTK window
  gtk_thread = std::thread(
    []() { gtk_app->make_window_and_run<tasdi2::MainWindow>(0, nullptr); });
  return true;
}
M64P_EXPORT void M64P_CALL InitiateControllers(CONTROL_INFO info) {
  info.Controls[0].Present = true;
  info.Controls[0].Plugin  = PLUGIN_NONE;
}
M64P_EXPORT void M64P_CALL GetKeys(int idx, BUTTONS* out) {
  using namespace std::literals;

  if (idx != 0) {
    out->Value = 0;
    return;
  }
  std::atomic<uint32_t> buttons = 0;
  std::atomic<bool> buttons_set = false;
  // Grab button inputs
  Glib::signal_idle().connect(
    [&]() {
      buttons     = get_main_window<tasdi2::MainWindow>().get_input().Value;
      buttons_set = true;
      buttons_set.notify_one();
      return false;
    },
    Glib::PRIORITY_HIGH_IDLE);
  buttons_set.wait(false);
  out->Value = buttons;
}
M64P_EXPORT void M64P_CALL ControllerCommand(int idx, unsigned char* cmd) {
  // This function can be used to interact with controller addons.
  // SM64 doesn't use any of them, so we should be fine for testing.
  (void) 0;
}
M64P_EXPORT void M64P_CALL ReadController(int idx, unsigned char* cmd) {
  // This function is currently useless, but M64+ leaves it here for later.
  (void) 0;
}
M64P_EXPORT void M64P_CALL RomClosed() {
  gtk_window_destroy(get_main_window<tasdi2::MainWindow>().gobj());
  if (gtk_thread->joinable())
    gtk_thread->join();
  gtk_thread = std::nullopt;
}

M64P_EXPORT void M64P_CALL SDL_KeyDown(int km, int ks) {}
M64P_EXPORT void M64P_CALL SDL_KeyUp(int km, int ks) {}
}