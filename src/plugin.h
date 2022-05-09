#ifndef _TASDI_PLUGIN_H_
#define _TASDI_PLUGIN_H_
#include <mupen64plus/m64p_plugin.h>
#include <mupen64plus/m64p_types.h>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void GetKeys(int idx, BUTTONS* out);
EXPORT void InitiateControllers(CONTROL_INFO info);
EXPORT int RomOpen();
EXPORT void RomClosed();

EXPORT void SDL_KeyDown(int km, int ks);
EXPORT void SDL_KeyUp(int km, int ks);


#ifdef __cplusplus
}
#endif
#endif