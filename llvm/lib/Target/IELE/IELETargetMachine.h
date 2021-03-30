// IELETargetMachine.h - Define TargetMachine for IELE -*- C++ -*-
//
//===----------------------------------------------------------------------===//
///
/// This file declares the IELE-specific subclass of
/// IELE.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_IELE_IELETARGETMACHINE_H
#define LLVM_LIB_TARGET_IELE_IELETARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {

class IELETargetMachine final : public LLVMTargetMachine {

public:
  IELETargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                    CodeGenOpt::Level OL, bool JIT);

  ~IELETargetMachine() override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  bool usesPhysRegsForValues() const override { return false; }

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_IELE_IELETARGETMACHINE_H
