#include "plugin.hpp"
#include "glibmm/main.h"
#include "glibmm/priorities.h"
#include "joystick.hpp"
#include "main_window.hpp"
#include "mupen64plus/m64p_types.h"
#include "mupen_api.hpp"

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <thread>

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
M64P_EXPORT m64p_error PluginStartup(
  m64p_dynlib_handle dll, void* data, debug_callback_t* debug_callback) {
  mupen_debug   = debug_callback;
  debug_context = data;
  // Start up GTK
  gtk_app = Gtk::Application::create("io.github.jgcodes2020.tasdi2");
  gtk_app->signal_activate().connect([]() {
    { tasdi2::Joystick(); }
  });

  init_flag = true;
  return M64ERR_SUCCESS;
}
M64P_EXPORT m64p_error PluginShutdown() {
  // Shut down GTK
  gtk_app.reset();

  init_flag = false;
  return M64ERR_SUCCESS;
}
M64P_EXPORT m64p_error PluginGetVersion(
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

M64P_EXPORT void ControllerCommand(int idx, unsigned char* cmd) {
  // This function can be used to interact with controller addons.
  // SM64 doesn't use any of them, so we should be fine for testing.
  (void) 0;
}
M64P_EXPORT void ReadController(int idx, unsigned char* cmd) {
  // This function is currently useless, but M64+ leaves it here for later.
  (void) 0;
}

M64P_EXPORT void InitiateControllers(CONTROL_INFO info) {
  info.Controls[0].Present = true;
  info.Controls[0].Plugin = PLUGIN_NONE;
}
M64P_EXPORT void GetKeys(int idx, BUTTONS* out) {
  if (idx != 0) {
    tasdi2::debug_log(
      M64MSG_ERROR, "This plugin is still in the works: it only supports P1.");
    tasdi2::debug_log(M64MSG_ERROR, "Commencing self-destruction protocol...");
    std::abort();
  }
  std::atomic<uint32_t> buttons = 0;
  // Grab button inputs
  Glib::signal_idle().connect(
    [&]() {
      buttons = get_main_window<tasdi2::MainWindow>().retrieve_input(0).Value;
      return false;
    },
    Glib::PRIORITY_HIGH_IDLE);
  buttons.wait(0);
  out->Value = buttons;
}
M64P_EXPORT int RomOpen() {
  // Init GTK window
  gtk_thread = std::thread(
    []() { gtk_app->make_window_and_run<tasdi2::MainWindow>(0, nullptr); });
  return true;
}
M64P_EXPORT void RomClosed() {
  get_main_window<tasdi2::MainWindow>().close();
}

M64P_EXPORT void SDL_KeyDown(int km, int ks) {}
M64P_EXPORT void SDL_KeyUp(int km, int ks) {}
}