find_package(PkgConfig REQUIRED)

function(pc_find_package name)
  string(REGEX REPLACE "([<>=]|[<>]=).+" "" base_name ${name})
  set(internal_name "pkg_config_target_${base_name}")
  
  pkg_check_modules(LIB "${name}")
  
  if (NOT LIB_FOUND)
    if (WIN32)
      message(FATAL_ERROR "CMake couldn't find the package `${name}`. \
Try running `pacman -Ss ${name}` (without the backticks, of course) to \
find a package for `${name}`, then run `pacman -S <name>` to install it.
")
    else()
      message(FATAL_ERROR "CMake couldn't find the package `${name}`. \
Please install the package for `${name}` first. (I assume that you know \
how to do that.)")
    endif()
  endif()
  # Set properties
  add_library("${internal_name}" INTERFACE)
  target_include_directories("${internal_name}" INTERFACE ${LIB_INCLUDE_DIRS})
  target_link_libraries("${internal_name}" INTERFACE ${LIB_LIBRARIES})
  target_link_directories("${internal_name}" INTERFACE ${LIB_LIBRARY_DIRS})
  target_compile_options("${internal_name}" INTERFACE ${LIB_CFLAGS_OTHER})
  target_link_options("${internal_name}" INTERFACE ${LIB_LDFLAGS_OTHER})
  
  add_library("pc::${base_name}" ALIAS ${internal_name})
endfunction()