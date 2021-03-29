include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_component_library(LLVMIELEInfo
  IELETargetInfo.cpp
  )

#add_dependencies(LLVMIELEInfo IELECommonTableGen)
