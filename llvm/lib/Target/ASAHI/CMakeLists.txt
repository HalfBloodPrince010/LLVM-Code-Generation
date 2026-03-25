add_llvm_component_group(ASAHI)

add_llvm_target(ASAHICodeGen
    ASAHIISelLowering.cpp
    ASAHITargetMachine.cpp
    ASAHITargetTransformInfo.cpp
    ASAHISubtarget.cpp

    LINK_COMPONENTS
    ASAHIDesc
    ASAHIInfo

    Analysis
    CodeGen
    Core
    MC
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
