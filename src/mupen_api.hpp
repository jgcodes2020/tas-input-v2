#ifndef _TASDI2_MUPEN_API_HPP_
#define _TASDI2_MUPEN_API_HPP_
/*
Small header to fix Mupen's lack of care for overriding things.
*/

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
#endif