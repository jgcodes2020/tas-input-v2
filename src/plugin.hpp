#ifndef _TASDI_PLUGIN_H_
#define _TASDI_PLUGIN_H_

#include <string_view>

#define M64P_PLUGIN_PROTOTYPES 1
#include <mupen64plus/m64p_plugin.h>
#include <mupen64plus/m64p_types.h>

// Redo Mupen import/export/call
#undef EXPORT
#undef IMPORT
#undef CALL

// Mupen64 dynamic library handle stuff
#if defined(WIN32)
  #define M64P_IMPORT extern "C" __declspec(dllimport)
  #define M64P_EXPORT __declspec(dllexport)
  #define M64P_CALL   __cdecl
  typedef HMODULE m64p_dynlib_handle;
#else
  #define M64P_IMPORT extern "C"
  #define M64P_EXPORT __attribute__((visibility("default")))
  #define M64P_CALL
  typedef void * m64p_dynlib_handle;
#endif



namespace tasdi2 {
  void debug_log(int log_level, const char* str);
}
#endif