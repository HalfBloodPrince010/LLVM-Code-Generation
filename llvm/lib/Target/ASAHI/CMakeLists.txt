add_llvm_component_group(ASAHI)

add_llvm_target(ASAHICodeGen
    ASAHIISelLowering.cpp
    ASAHITargetMachine.cpp
    ASAHISubtarget.cpp

    LINK_COMPONENTS
    ASAHIDesc
    ASAHIInfo

    CodeGen
    Core
    MC
    SelectionDAG
    Support
    Target

    ADD_TO_COMPONENT
    ASAHI
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
