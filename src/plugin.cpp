#include "plugin.h"

extern "C" {
EXPORT void ControllerCommand(int idx, unsigned char* command);
EXPORT void GetKeys(int idx, BUTTONS* out);
EXPORT int RomOpen();
EXPORT void RomClosed();

EXPORT void SDL_KeyDown(int km, int ks);
EXPORT void SDL_KeyUp(int km, int ks);
}