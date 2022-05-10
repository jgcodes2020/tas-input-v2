cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(tas-input-v2
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Just for fanciness
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Make sure they're not dumb.
include(PlatformChecks)

# Packages and Mupen headers
include(PkgConfigTargets)
pc_find_package(gtkmm-4.0)
include(M64PApi)

# Resources
include(Resources)
compile_resource(main.css "css/main.css" "css_data" "tasdi2::rsrc")
compile_resource(main.ui "ui/main.ui" "ui_data" "tasdi2::rsrc")

# UI test executable

# UI test executable
add_library(tasdi2 SHARED
  "src/plugin.cpp"
  "src/plugin.hpp"
  "src/joystick.cpp"
  "src/joystick.hpp"
  "src/main_window.cpp"
  "src/main_window.hpp"
  ${main.css}
  ${main.ui}
  "src/mupen_api.hpp"
)
target_include_directories(tasdi2 PRIVATE "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include")
target_link_libraries(tasdi2 PRIVATE pc::gtkmm-4.0)
target_compile_features(tasdi2 PRIVATE cxx_std_20)