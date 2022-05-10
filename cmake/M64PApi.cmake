if (REFRESH_MUPEN_API OR NOT MUPEN_API_DOWNLOADED)
  set(MUPEN_API_DOWNLOADED TRUE CACHE INTERNAL "True if Mupen has been downloaded.")
  unset(REFRESH_MUPEN_API CACHE)
  # Download rerecording (in case of API differences)
  file(DOWNLOAD "https://github.com/Madghostek/mupen64plus-core-rr/archive/master.tar.gz"
    "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/mupen.tar.gz"
  )
  # Extract the correct dir
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar -xzvf "mupen.tar.gz" mupen64plus-core-rr-master/src/api
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp"
  )
  # Clear old API files
  file(REMOVE_RECURSE 
    "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include/mupen64plus")
  # List API headers
  file(GLOB api_header_list 
    RELATIVE "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/mupen64plus-core-rr-master/src/api/" 
    "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/mupen64plus-core-rr-master/src/api/m64p_*.h"
  )

  file(MAKE_DIRECTORY 
    "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include/mupen64plus/")
  foreach (i IN LISTS api_header_list)
    file(RENAME
      "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/mupen64plus-core-rr-master/src/api/${i}"
      "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include/mupen64plus/${i}"
    )
  endforeach()

  # Clear temporary files
  file(REMOVE 
    "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/mupen.tar.gz")
  file(REMOVE_RECURSE 
    "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/mupen64plus-core-rr-master")
endif()