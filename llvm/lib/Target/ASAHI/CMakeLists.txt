add_llvm_component_group(ASAHI)

add_llvm_target(ASAHICodeGen
    ASAHITargetMachine.cpp

    LINK_COMPONENTS
    ASAHIMCDesc
    ASAHITargetInfo

    Support

    ADD_TO_COMPONENT
    ASAHI
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
