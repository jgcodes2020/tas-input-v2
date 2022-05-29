#ifndef _TASDI2_MUPEN_API_HPP_
#define _TASDI2_MUPEN_API_HPP_
/*
Small header to fix Mupen's lack of care for overriding things.
*/

#define M64P_PLUGIN_PROTOTYPES 1
#include <mupen64plus/m64p_plugin.h>
#include <mupen64plus/m64p_vcr.h>


// Redo Mupen import/export/call
#undef EXPORT
#undef IMPORT
#undef CALL

// Mupen64 dynamic library handle stuff
#if defined(WIN32)
  #define M64P_IMPORT extern "C" __declspec(dllimport)
  #define M64P_EXPORT __declspec(dllexport)
  #define M64P_CALL   __cdecl
#else
  #define M64P_IMPORT extern "C"
  #define M64P_EXPORT __attribute__((visibility("default")))
  #define M64P_CALL
#endif

// Windows bad
#undef ERROR
#undef IN
#undef OUT
#undef WINDING
#undef IGNORE

// Dang you Madghostek
#undef BOOL

#endif