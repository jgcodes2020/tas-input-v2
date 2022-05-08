# TASInput v2

This project is a Mupen64Plus input plugin that provides a GUI for precise joystick and button input.

## Building instructions
### Linux
Install your distribution's packages for gtkmm 4, along with cmake. Then, simply build like you would any other CMake project:
```sh
mkdir build && cd build
cmake ..
cmake --build .
```
- Note: depending on your distribution, you may not have access to gtkmm 4 from the repositories. In this case, you'll need to build it from source, then make it available to pkg-config somehow. (This package uses pkg-config to find `gtkmm`.)

### Windows
[Install](https://www.msys2.org/#installation) MSYS2 and the MinGW toolchain. Then, open *MSYS2 MinGW x64* install gtkmm 4:
```sh
# This may be slightly different, depending on which MSYS toolchain you use.
pacman -S mingw-w64-x86_64-gtkmm-4.0
```
Install CMake. **Make sure you use MinGW CMake and not MSYS CMake. You will encounter an error if you fail to use the correct CMake.**
```sh
# This may be slightly different, depending on which MSYS toolchain you use.
pacman -S mingw-w64-x86_64-cmake
```
Now, you can simply build like you would any other CMake project:
```sh
mkdir build && cd build
cmake ..
cmake --build .
```