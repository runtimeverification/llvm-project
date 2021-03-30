//===-- IELE.h - Top-level interface for IELE  ----*- C++ -*-===//
//
//===----------------------------------------------------------------------===//
///
/// This file contains the entry points for global functions defined in
/// the LLVM IELE back-end.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_IELE_IELE_H
#define LLVM_LIB_TARGET_IELE_IELE_H

#include "llvm/PassRegistry.h"
#include "llvm/Support/CodeGen.h"

namespace llvm {

class IELETargetMachine;
class ModulePass;
class FunctionPass;

// LLVM IR passes.

// ISel and immediate followup passes.
FunctionPass *createIELEISelDag(IELETargetMachine &TM,
                                CodeGenOpt::Level OptLevel);

// Late passes.

// PassRegistry initialization declarations.


} // end namespace llvm

#endif // LLVM_LIB_TARGET_IELE_IELE_H
