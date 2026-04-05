//===-- ASAHI.h - ASAHI specific passes ---------------------------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file hold the declarations for the ASAHI-specific passes for
// both the legacy and new pass managers.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ASAHI_ASAHI_H
#define LLVM_LIB_TARGET_ASAHI_ASAHI_H

#include "llvm/IR/PassManager.h" // For PassInfoMixin
#include "llvm/PassRegistry.h"

namespace llvm {

class Function;
class Pass;
class PassRegistry;

// Using new pass manager
class ASAHISimpleConstantPropagationNewPass : public llvm::PassInfoMixin<ASAHISimpleConstantPropagationNewPass> {
public:
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &AM);
};


// For legacy Pass manager
// This is to setup the metadata in th pass registry, to show this pass exists. Doesn't run the pass
void initializeASAHISimpleConstantPropagationPass(PassRegistry  &);
// Used by PM.addPass(createASAHISimpleConstantPropagationPassForLegacyPM) .. to actually run the pass
Pass *createASAHISimpleConstantPropagationPassForLegacyPM();
}

#endif // LLVM_LIB_TARGET_ASAHI_ASAHI_H