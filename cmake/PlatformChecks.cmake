if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "^MINGW")
  # Ensure MinGW cmake, not MSYS cmake
  execute_process(
    COMMAND pacman -Qs "^mingw-w64(-(ucrt|clang))?-(i686|x86_64)-cmake$"
    OUTPUT_QUIET
    ERROR_QUIET
    RESULT_VARIABLE mingw_cmake_found
  )
  if (NOT mingw_cmake_found EQUAL 0)
    message(FATAL_ERROR "You are using MSYS CMake, which cannot build this package. \
Please use MinGW CMake: https://www.msys2.org/docs/cmake/")
  endif()
endif()