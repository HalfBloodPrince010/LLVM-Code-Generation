# Note even though we name it LLVMASAHIMCDesc, it is referenced as ASAHIMCDesc in LINK_COMPONENTS
add_llvm_component_library(LLVMASAHIDesc
    ASAHIMCTargetDesc.cpp

    LINK_COMPONENTS
    Support

    ADD_TO_COMPONENT
    ASAHI
)
