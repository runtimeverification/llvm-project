//===--- IELETargetMachine.cpp - Define TargetMachine for IELE          ---===//
//
//===----------------------------------------------------------------------===//
///
/// This file defines the WebAssembly-specific subclass of TargetMachine.
///
//===----------------------------------------------------------------------===//

#include "IELETargetMachine.h"
#include "TargetInfo/IELETargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define DEBUG_TYPE "iele"


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeIELETarget() {
  // Register the target.
  RegisterTargetMachine<IELETargetMachine> X(
      getTheIELETarget());
}

//===----------------------------------------------------------------------===//
// WebAssembly Lowering public interface.
//===----------------------------------------------------------------------===//

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue()) {
    // Default to static relocation model.
    return Reloc::Static;
  }

  return *RM;
}

/// Create an WebAssembly architecture model.
///
IELETargetMachine::IELETargetMachine(
    const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
    const TargetOptions &Options, Optional<Reloc::Model> RM,
    Optional<CodeModel::Model> CM, CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:64:64-i64:64-n32:64-S128",
                        TT, CPU, FS, Options, getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Large), OL) {
  // From WebAssembly: We lower LLVM 'unreachable' to ISD::TRAP.
  this->Options.TrapUnreachable = true;

  // From WebAssembly: We treat each function as an independent unit. Force
  // -ffunction-sections, effectively, so that we can emit them independently.
  this->Options.FunctionSections = true;
  this->Options.DataSections = true;
  this->Options.UniqueSectionNames = true;

//  initAsmInfo();

  // Note that we don't use setRequiresStructuredCFG(true). It disables
  // optimizations than we're ok with, and want, such as critical edge
  // splitting and tail merging.
}

IELETargetMachine::~IELETargetMachine() = default; // anchor.

