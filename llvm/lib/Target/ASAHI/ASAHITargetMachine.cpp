#include "ASAHI.h"
#include "ASAHITargetObjectFile.h"
#include "ASAHITargetMachine.h"
#include "ASAHITargetTransformInfo.h"
#include "llvm/Support/Compiler.h"  // LLVM_EXTERNAL_VISIBILITY
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"     // For RegisterTargetMachine.
#include "llvm/Passes/PassBuilder.h"
#include "TargetInfo/ASAHITargetInfo.h"  // For getTheAsahiTarget
#include <memory>

using namespace llvm;

static std::unique_ptr<TargetLoweringObjectFile> createTLOF(const Triple &TT) {
    if(TT.isOSBinFormatELF()) {
        return std::make_unique<ASAHI_ELFTargetObjectFile>();
    } else if (TT.isOSBinFormatMachO()) {
        return std::make_unique<ASAHI_MachoTargetObjectFile>();
    }

    // Other format not supported yet.
    return nullptr;
}

static const char *ASAHIDataLayoutStr =
    "e-p:16:16:16-n16:32-i32:32:32-i16:16:16-i1:8:8-f32:32:32-v32:32:32";


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeASAHITarget() {
    // Just like how we register the Target in TargetRegistry, we need
    // to register TargetMachine as well, but in the TargetMachineRegistry
    RegisterTargetMachine<ASAHITargetMachine> X(getTheAsahiTarget());

    PassRegistry &PR = *PassRegistry::getPassRegistry();
    initializeASAHISimpleConstantPropagationPass(PR);

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
                               CM ? *CM: CodeModel::Small, OL),
      TLOF(createTLOF(getTargetTriple())) {
        initAsmInfo();
    }
    // CodeModel::Small means the target object file is small and can be fit under 2GB
    // Needed to decide the addressing modes and other details

ASAHITargetMachine::~ASAHITargetMachine() = default;



/*
Target Machine --uses/calls--> Subtarget --uses/calls--> TargetLowering

Ideally, we do the following

IR → SelectionDAG
LegalizeTypes
Legalize
DAG combines
Instruction selection (match DAG patterns to real instructions)

This is the SelectionDAG pipeline.

This is invoked during -O1 or -O2 optimization?
*/
const ASAHISubtarget *
ASAHITargetMachine::getSubtargetImpl(const Function &F) const {
    Attribute CPUAttr = F.getFnAttribute("target-cpu");
    Attribute FSAttr =  F.getFnAttribute("target-features");

    StringRef CPU = CPUAttr.isValid() ? CPUAttr.getValueAsString() : TargetCPU;
    StringRef FS = FSAttr.isValid() ? FSAttr.getValueAsString() : TargetFS;

    // Eventually, we'll want to hook up a different subtarget based on at the
    // target feature, target cpu, and tune cpu attached to F, but as of now,
    // the target doesn't support anything fancy so we just have one subtarget
    // for everything.
    if(!SubtargetSingleton){
        SubtargetSingleton = std::make_unique<ASAHISubtarget>(TargetTriple, CPU, FS, *this);
    }

    return SubtargetSingleton.get();
}

TargetTransformInfo
ASAHITargetMachine::getTargetTransformInfo(const Function &F) const {
    return TargetTransformInfo(ASAHITTIImpl(this, F));
}

// Helps with the registration of --- opt -passes="asahi-simple-cst-prop"
// “If someone asks for a pass named asahi-simple-cst-prop, construct ASAHISimpleConstantPropagationNewPass().”
// That is registration / discoverability.
void ASAHITargetMachine::registerPassBuilderCallbacks(PassBuilder &PB) {
#define GET_PASS_REGISTRY "ASAHIPassRegistry.def"
#include "llvm/Passes/TargetPassRegistry.inc"

  // Contrary to the above, this says
  // Whenever LLVM builds the default optimization pipeline, automatically include this pass.
  PB.registerPipelineStartEPCallback(
    [](ModulePassManager &MPM, OptimizationLevel optLevel) {
        // Do not add optimization passes if we are in O0.
        if(optLevel == OptimizationLevel::O0) {
            return;
        }

        FunctionPassManager FPM;
        FPM.addPass(ASAHISimpleConstantPropagationNewPass());
        MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
    });
}

TargetPassConfig* ASAHITargetMachine::createPassConfig(PassManagerBase &PM) {
    return new ASAHIPassConfig(*this, PM);
}

ASAHIPassConfig::ASAHIPassConfig(TargetMachine &TM, PassManagerBase &PM) : TargetPassConfig(TM, PM) {

}

bool ASAHIPassConfig::addInstSelector() {
    // TODO: We need to hook up the DAG selector here.
    return false;
}
