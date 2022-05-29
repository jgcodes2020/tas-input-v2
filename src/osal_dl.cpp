#include "osal_dl.hpp"
#include <stdexcept>

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
void* osal_dlsym(m64p_dynlib_handle hnd, const char* name) {
  dlerror();
  void* res = dlsym(hnd, name);
  const char* err = dlerror();
  if (err) {
    throw std::runtime_error(err);
  }
  return res;
}
#elif defined(_WIN32)
#include <windows.h>
#include <system_error>
void* osal_dlsym(m64p_dynlib_handle hnd, const char* name) {
  SetLastError(0);
  FARPROC res = GetProcAddress(hnd, name);
  int err = GetLastError();
  if (err != 0) {
    throw std::system_error(err, std::system_category());
  }
  return reinterpret_cast<void*>(res);
}
#endif