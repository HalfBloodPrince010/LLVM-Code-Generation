add_llvm_component_library(LLVMASAHIInfo
    ASAHITargetInfo.cpp

    LINK_COMPONENTS
    Support

    ADD_TO_COMPONENT
    ASAHI
)