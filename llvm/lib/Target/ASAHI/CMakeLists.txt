add_llvm_component_group(ASAHI)

add_llvm_target(ASAHICodeGen
    ASAHIISelLowering.cpp
    ASAHISimpleConstantPropagation.cpp
    ASAHISubtarget.cpp
    ASAHITargetMachine.cpp
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
