//=-- ASAHITargetMachine.h - Define TargetMachine for ASAHI Target -*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the ASAHI specific TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ASAHI_ASAHITARGETMACHINE_H
#define LLVM_LIB_TARGET_ASAHI_ASAHITARGETMACHINE_H

#include "ASAHISubtarget.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include <memory>
#include <optional>

namespace llvm {

class ASAHITargetMachine: public CodeGenTargetMachineImpl {
    mutable std::unique_ptr<ASAHISubtarget> SubtargetSingleton;
    std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
    ASAHITargetMachine(const Target &T, const Triple &TT, StringRef CPU, 
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);

    ~ASAHITargetMachine() override;

    const ASAHISubtarget *getSubtargetImpl(const Function &F) const override;
    TargetTransformInfo getTargetTransformInfo(const Function &F) const override;

    TargetLoweringObjectFile *getObjFileLowering() const override {
        return TLOF.get();
    }

    // Register the target specific passes that this backend offers.
    void registerPassBuilderCallbacks(PassBuilder &PB) override;
    TargetPassConfig* createPassConfig(PassManagerBase &PM) override;
};

class ASAHIPassConfig : public TargetPassConfig {
public:
    ASAHIPassConfig(TargetMachine &TM, PassManagerBase &PM);

    bool addInstSelector() override;
};

} // namespace llvm

#endif
