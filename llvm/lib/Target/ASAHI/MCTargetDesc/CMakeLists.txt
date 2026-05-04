# Note even though we name it LLVMASAHIMCDesc, it is referenced as ASAHIMCDesc in LINK_COMPONENTS
add_llvm_component_library(LLVMASAHIDesc
    ASAHIMCAsmInfo.cpp
    ASAHIMCTargetDesc.cpp
    ASAHIInstPrinter.cpp

    LINK_COMPONENTS
    Support
    ASAHIInfo
    MC

    ADD_TO_COMPONENT
    ASAHI
)
