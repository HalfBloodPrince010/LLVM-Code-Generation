
#include "ASAHIMCTargetDesc.h"
#include "TargetInfo/ASAHITargetInfo.h" // getTheASAHITarget
#include "llvm/Support/Compiler.h" // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

#define GET_SUBTARGETINFO_MC_DESC
#include "ASAHIGenSubtargetInfo.inc"

static MCSubtargetInfo *
createASAHIMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
    return createASAHIMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeASAHITargetMC() {
    Target &TheTarget = getTheASAHITarget();

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(TheTarget, createASAHIMCSubtargetInfo);
}
