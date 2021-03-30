set(LLVM_TARGET_DEFINITIONS IELE.td)

#add_public_tablegen_target(X86CommonTableGen)

set(sources
  IELEISelDAGToDAG.cpp
  IELETargetMachine.cpp
  )

add_llvm_target(IELECodeGen ${sources})

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
