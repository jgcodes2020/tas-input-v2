find_package(PkgConfig REQUIRED)

function(pc_find_package name)
  string(REGEX REPLACE "([<>=]|[<>]=).+" "" base_name ${name})
  set(internal_name "pkg_config_target_${base_name}")
  
  pkg_check_modules(LIB REQUIRED ${name})
  
  # MSYS hack: change all pkg-config paths to Unix
  if (MINGW OR MSYS)
    list(LENGTH LIB_INCLUDE_DIRS len)
    math(EXPR last "${len} - 1")
    foreach (i RANGE "${last}")
      list(GET LIB_INCLUDE_DIRS "${i}" win_path)
      execute_process(
        COMMAND cygpath -u "${win_path}"
        OUTPUT_VARIABLE unix_path
      )
      list(REMOVE_AT LIB_INCLUDE_DIRS "${i}")
      list(INSERT LIB_INCLUDE_DIRS "${i}" "${unix_path}")
    endforeach()
    
    list(LENGTH LIB_LIBRARY_DIRS len)
    math(EXPR last "${len} - 1")
    foreach (i RANGE "${last}")
      list(GET LIB_LIBRARY_DIRS "${i}" win_path)
      execute_process(
        COMMAND cygpath -u "${win_path}"
        OUTPUT_VARIABLE unix_path
      )
      list(REMOVE_AT LIB_LIBRARY_DIRS "${i}")
      list(INSERT LIB_LIBRARY_DIRS "${i}" "${unix_path}")
    endforeach()
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