add_llvm_component_library(LLVMASAHIInfo
    ASAHITargetInfo.cpp

    LINK_COMPONENTS
    MC
    Support
    TextAPI

    ADD_TO_COMPONENT
    ASAHI
)