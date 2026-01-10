#include "ASAHITargetMachine.h"
#include "llvm/Support/Compiler.h"  // LLVM_EXTERNAL_VISIBILITY
#include "llvm/MC/TargetRegistry.h"     // For RegisterTargetMachine.
#include "TargetInfo/ASAHITargetInfo.h"  // For getTheAsahiTarget

using namespace llvm;

static const char *ASAHIDataLayoutStr =
    "e-p:16:16:16-n16:32-i32:32:32-i16:16:16-i1:8:8-f32:32:32-v32:32:32";


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeASAHITarget() {
    // Just like how we register the Target in TargetRegistry, we need
    // to register TargetMachine as well, but in the TargetMachineRegistry
    RegisterTargetMachine<ASAHITargetMachine> X(getTheAsahiTarget());

}

ASAHITargetMachine::ASAHITargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, ASAHIDataLayoutStr, TT, CPU, FS, Options,
                               // Use the simplest relocation by default
                               RM ? *RM: Reloc::Static,
                               CM ? *CM: CodeModel::Small, OL) {}
    // CodeModel::Small means the target object file is small and can be fit under 2GB
    // Needed to decide the addressing modes and other details

ASAHITargetMachine::~ASAHITargetMachine() = default;
