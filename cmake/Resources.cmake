find_package(Python REQUIRED COMPONENTS Interpreter)

function(compile_resource output source symbol namespace)
  set("${output}" "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include/resources/${source}.rsrc.hpp" PARENT_SCOPE)
  set(outpath "${PROJECT_BINARY_DIR}/CMakeFiles/gen-include/resources/${source}.rsrc.hpp")
  
  if (IS_ABSOLUTE ${source})
    set(srcpath ${source})
  else()
    set(srcpath "${PROJECT_SOURCE_DIR}/res/${source}")
  endif()
  
  add_custom_command(OUTPUT ${outpath}
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/rsrcc.py ${srcpath} ${symbol} -o ${outpath} -n ${namespace}
    DEPENDS ${srcpath}
  )
endfunction()