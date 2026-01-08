add_llvm_component_library(LLVMASAHITargetInfo
    ASAHITargetInfo.cpp

    LINK_COMPONENTS
    Support

    ADD_TO_COMPONENT
    ASAHI
)