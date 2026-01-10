#include "ASAHITargetInfo.h"
#include "llvm/MC/TargetRegistry.h" // For RegisterTarget.
#include "llvm/Support/Compiler.h"  // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/TextAPI/Target.h"    // For Target class.

using namespace llvm;

Target &llvm::getTheAsahiTarget() {
    static Target TheAsahiTarget;
    return TheAsahiTarget;
}


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeASAHITargetInfo() {

    RegisterTarget<Triple::asahi, /*HasJIT=*/false> X(
        getTheAsahiTarget(),
        /*name*/"asahi",
        /*Desc*/"Sample asahi backend",
        /*BackendName*/"ASAHI"
    );
}
