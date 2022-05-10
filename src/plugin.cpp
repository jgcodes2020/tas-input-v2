#include "plugin.hpp"
#include "joystick.hpp"
#include "main_window.hpp"
#include "mupen64plus/m64p_types.h"

#include <atomic>
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
  
  
}  // namespace
namespace tasdi2 {
  void debug_log(int log_level, const char* out) {
    if (!init_flag) {
      throw std::runtime_error("Cannot call debug() before plugin initializes");
    }
    mupen_debug(debug_context, log_level, out);
  }

  extern "C" {
  M64P_EXPORT m64p_error PluginStartup(
    m64p_dynlib_handle dll, void* data, debug_callback_t* debug_callback) {
    mupen_debug   = debug_callback;
    debug_context = data;

    // Initialize derived widgets for GType
    { tasdi2::Joystick(); }

    // Start up GTK
    gtk_app = Gtk::Application::create("io.github.jgcodes2020.tasdi2");
    
    init_flag = true;
    return M64ERR_SUCCESS;
  }
  M64P_EXPORT m64p_error PluginShutdown() {
    // Shut down GTK
    gtk_app.reset();
    
    init_flag = false;
    return M64ERR_SUCCESS;
  }
  m64p_error PluginGetVersion(
    m64p_plugin_type* type, int* version, int* api_version,
    const char** plugin_name, int* caps);

  M64P_EXPORT void InitiateControllers(CONTROL_INFO info) {
    
  }
  M64P_EXPORT void GetKeys(int idx, BUTTONS* out);
  M64P_EXPORT int RomOpen();
  M64P_EXPORT void RomClosed();

  M64P_EXPORT void SDL_KeyDown(int km, int ks);
  M64P_EXPORT void SDL_KeyUp(int km, int ks);
  }
}  // namespace tasdi2