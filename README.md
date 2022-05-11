# TASInput2

This project is a Mupen64Plus input plugin that provides a GUI for precise joystick and button input.

While the UI is heavily inspired by the original TASInput, this project shares no code with it.

## Building instructions
### Linux
Install your distribution's packages for GTKmm 4, along with cmake. Take note that Debian/Ubuntu do not offer GTKmm 4
Then, simply build like you would any other CMake project:
```sh
mkdir build && cd build
cmake ..
cmake --build .
```
**Note:** Distributions based on Debian/Ubuntu do not ship GTKmm 4 in their repositories. You'll need to build it from source, and setup a pkg-config file (either in the system or in `<project root>/pc`).

### Windows (with MSYS)
[Install](https://www.msys2.org/#installation) MSYS2 and the MinGW toolchain. Then, open *MSYS2 MinGW x64* and install gtkmm 4:
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