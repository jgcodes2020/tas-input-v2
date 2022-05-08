if (WIN32 AND NOT MINGW)
  # Make sure the user is in MSYS (only MSYS has pacman)
  find_program(PACMAN "pacman" NO_CACHE)
  if (NOT PACMAN)
    message(FATAL_ERROR "pacman was not found on your PATH. This is likely because of either:\
  a) you haven't installed MSYS2 and MinGW
  b) you're running CMake from outside MSYS/MinGW
If you need to install MSYS/MinGW, refer to their docs here: https://www.msys2.org/#installation")
  endif()
  
  # Ensure MinGW cmake, not MSYS cmake
  execute_process(
    COMMAND pacman -Qs "^mingw-w64(-(ucrt|clang))?-(i686|x86_64)-cmake$"
    OUTPUT_QUIET
    ERROR_QUIET
    RESULT_VARIABLE mingw_cmake_found
  )
  if (NOT mingw_cmake_found EQUAL 0)
    message(FATAL_ERROR "You are using MSYS CMake, which cannot build this package.\
Please use MinGW CMake: https://www.msys2.org/docs/cmake/")
  endif()
endif()