//===--- IELETargetMachine.cpp - Define TargetMachine for IELE          ---===//
//
//===----------------------------------------------------------------------===//
///
/// This file defines the IELE-specific subclass of TargetMachine.
///
//===----------------------------------------------------------------------===//

#include "IELETargetMachine.h"
#include "TargetInfo/IELETargetInfo.h"
#include "IELE.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define DEBUG_TYPE "iele"


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeIELETarget() {
  // Register the target.
  RegisterTargetMachine<IELETargetMachine> X(
      getTheIELETarget());
}

//===----------------------------------------------------------------------===//
// IELE Lowering public interface.
//===----------------------------------------------------------------------===//

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue()) {
    // Default to static relocation model.
    return Reloc::Static;
  }

  return *RM;
}

/// Create an IELE architecture model.
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

namespace {

/// IELE Code Generator Pass Configuration Options.
class IELEPassConfig final : public TargetPassConfig {
public:
  IELEPassConfig(IELETargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  IELETargetMachine &getIELETargetMachine() const {
    return getTM<IELETargetMachine>();
  }

  FunctionPass *createTargetRegisterAllocator(bool) override;

  void addIRPasses() override;
  bool addInstSelector() override;
  void addPostRegAlloc() override;
  bool addGCPasses() override { return false; }
  void addPreEmitPass() override;

  // No reg alloc
  bool addRegAssignmentFast() override { return false; }

  // No reg alloc
  bool addRegAssignmentOptimized() override { return false; }
};

} // end anonymous namespace

TargetPassConfig *
IELETargetMachine::createPassConfig(PassManagerBase &PM) {
  return new IELEPassConfig(*this, PM);
}

FunctionPass *IELEPassConfig::createTargetRegisterAllocator(bool) {
  return nullptr; // No reg alloc
}

//===----------------------------------------------------------------------===//
// The following functions are called from lib/CodeGen/Passes.cpp to modify
// the CodeGen pass sequence.
//===----------------------------------------------------------------------===//

void IELEPassConfig::addIRPasses() {
  // This is a no-op if atomics are not used in the module
  addPass(createAtomicExpandPass());

  // Expand indirectbr instructions to switches.
  addPass(createIndirectBrExpandPass());

  TargetPassConfig::addIRPasses();
}

bool IELEPassConfig::addInstSelector() {
  (void)TargetPassConfig::addInstSelector();
  addPass(
      createIELEISelDag(getIELETargetMachine(), getOptLevel()));

  return false;
}

void IELEPassConfig::addPostRegAlloc() {
  // From WebAssembly: The following CodeGen passes don't support code
  // containing virtual registers.

  // These functions all require the NoVRegs property.
  disablePass(&MachineCopyPropagationID);
  disablePass(&PostRAMachineSinkingID);
  disablePass(&PostRASchedulerID);
  disablePass(&FuncletLayoutID);
  disablePass(&StackMapLivenessID);
  disablePass(&LiveDebugValuesID);
  disablePass(&PatchableFunctionID);
  disablePass(&ShrinkWrapID);

  TargetPassConfig::addPostRegAlloc();
}

void IELEPassConfig::addPreEmitPass() {
  TargetPassConfig::addPreEmitPass();

}
