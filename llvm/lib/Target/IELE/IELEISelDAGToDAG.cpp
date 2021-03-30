//==--- IELEISelDAGToDAG.cpp - A dag to dag inst selector for IELE --------===//
//
//===----------------------------------------------------------------------===//
///
/// This file defines an instruction selector for the IELE target.
///
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/IELEMCTargetDesc.h"
#include "IELE.h"
#include "IELETargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/Function.h" // To access function attributes.
#include "llvm/Support/Debug.h"
#include "llvm/Support/KnownBits.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "iele-isel"

//===--------------------------------------------------------------------===//
/// IELE-specific code to select IELE machine instructions for SelectionDAG
/// operations.
///
namespace {
class IELEDAGToDAGISel final : public SelectionDAGISel {

public:
  IELEDAGToDAGISel(IELETargetMachine &TM,
                   CodeGenOpt::Level OptLevel)
      : SelectionDAGISel(TM, OptLevel) {
  }

  StringRef getPassName() const override {
    return "IELE Instruction Selection";
  }

  bool runOnMachineFunction(MachineFunction &MF) override {
    LLVM_DEBUG(dbgs() << "********** ISelDAGToDAG **********\n"
                         "********** Function: "
                      << MF.getName() << '\n');

    return SelectionDAGISel::runOnMachineFunction(MF);
  }

  void Select(SDNode *Node) override;

  bool SelectInlineAsmMemoryOperand(const SDValue &Op, unsigned ConstraintID,
                                    std::vector<SDValue> &OutOps) override;


private:
  // add select functions here...
};
} // end anonymous namespace

void IELEDAGToDAGISel::Select(SDNode *Node) {
}

bool IELEDAGToDAGISel::SelectInlineAsmMemoryOperand(
    const SDValue &Op, unsigned ConstraintID, std::vector<SDValue> &OutOps) {
  return true;
}

/// This pass converts a legalized DAG into a IELE-specific DAG, ready
/// for instruction scheduling.
FunctionPass *llvm::createIELEISelDag(IELETargetMachine &TM,
                                      CodeGenOpt::Level OptLevel) {
  return new IELEDAGToDAGISel(TM, OptLevel);
}
