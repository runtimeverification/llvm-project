//===--- IELEMCTargetDesc.cpp - WebAssembly Target Descriptions -----------===//
//
//===----------------------------------------------------------------------===//
///
/// This file provides IELE-specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/IELEMCTargetDesc.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define DEBUG_TYPE "iele-mc-target-desc"
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeIELETargetMC() {
}
