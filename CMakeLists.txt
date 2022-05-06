cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(tas-input-v2
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Just for fanciness
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(PkgConfigTargets)
pc_find_package(gtkmm-4.0)

include(Resources)
compile_resource(button_frame_css "css/button-frame.css" "css_data" "tasdi2::rsrc")
compile_resource(button_frame_ui "ui/button-frame.ui" "ui_data" "tasdi2::rsrc")

add_executable(testapp
  "src/main.cpp"
  "src/ButtonFrame.hpp"
  "src/ButtonFrame.cpp"
  ${button_frame_css}
  ${button_frame_ui}
)
target_include_directories(testapp PRIVATE "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include")
target_link_libraries(testapp pc::gtkmm-4.0)
target_compile_features(testapp PRIVATE cxx_std_20)