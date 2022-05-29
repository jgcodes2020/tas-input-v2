#ifndef _TASDI_PLUGIN_H_
#define _TASDI_PLUGIN_H_

#include <string_view>

#include "mupen_api.hpp"

namespace tasdi2 {
  void debug_log(int log_level, const char* str);
}

// Windows bad
#undef ERROR
#undef IN
#undef OUT
#undef WINDING
#undef IGNORE
#endif