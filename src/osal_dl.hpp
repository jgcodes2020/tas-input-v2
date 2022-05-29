#ifndef _TASDI2_OSAL_DL_HPP_
#define _TASDI2_OSAL_DL_HPP_

#include "mupen_api.hpp"
#include <string>
#include <string_view>

void* osal_dlsym(m64p_dynlib_handle hnd, const char* name);
inline void* osal_dlsym(m64p_dynlib_handle hnd, const std::string& name) {
  return osal_dlsym(hnd, name.c_str());
}
inline void* osal_dlsym(m64p_dynlib_handle hnd, std::string_view name) {
  std::string str(name);
  return osal_dlsym(hnd, str.c_str());
}

#endif