//===--- IELETargetInfo.cpp - IELE Target Implementation                ---===//
//
//===----------------------------------------------------------------------===//
///
/// This file registers the IELE target.
///
//===----------------------------------------------------------------------===//

#include "TargetInfo/IELETargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define DEBUG_TYPE "iele-target-info"

Target &llvm::getTheIELETarget() {
  static Target TheIELETarget;
  return TheIELETarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeIELETargetInfo() {
  RegisterTarget<Triple::iele> X(getTheIELETarget(), "iele", "IELE", "IELE");
}

