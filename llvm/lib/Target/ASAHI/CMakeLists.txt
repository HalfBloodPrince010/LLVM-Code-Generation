add_llvm_component_group(ASAHI)

set (LLVM_TARGET_DEFINITIONS ASAHI.td)

tablegen(LLVM ASAHIGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM ASAHIGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ASAHIGenInstrInfo.inc -gen-instr-info)
# MCInst to .s
tablegen(LLVM ASAHIGenAsmWriter.inc -gen-asm-writer)
# .s to MCInst
tablegen(LLVM ASAHIGenAsmMatcher.inc -gen-asm-matcher)
# Encoding.
tablegen(LLVM ASAHIGenMCCodeEmitter.inc -gen-emitter)

add_public_tablegen_target(ASAHICommonTableGen)

add_llvm_target(ASAHICodeGen
    ASAHIISelLowering.cpp
    ASAHISimpleConstantPropagation.cpp
    ASAHISubtarget.cpp
    ASAHIInstrInfo.cpp
    ASAHIFrameLowering.cpp
    ASAHITargetMachine.cpp
    ASAHITargetObjectFile.cpp
    ASAHITargetTransformInfo.cpp

    LINK_COMPONENTS
    ASAHIDesc
    ASAHIInfo

    Analysis
    CodeGen
    Core
    MC
    Passes
    SelectionDAG
    Support
    Target
    TargetParser
    TransformUtils

    ADD_TO_COMPONENT
    ASAHI
)

add_subdirectory(AsmParser)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
