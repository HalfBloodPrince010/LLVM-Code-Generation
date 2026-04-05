add_llvm_component_group(ASAHI)

set (LLVM_TARGET_DEFINITIONS ASAHI.td)

tablegen(LLVM ASAHIGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(ASAHICommonTableGen)

add_llvm_target(ASAHICodeGen
    ASAHIISelLowering.cpp
    ASAHISimpleConstantPropagation.cpp
    ASAHISubtarget.cpp
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

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
