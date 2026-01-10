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

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {

class ASAHITargetMachine: public CodeGenTargetMachineImpl {
public:
    ASAHITargetMachine(const Target &T, const Triple &TT, StringRef CPU, 
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);

    ~ASAHITargetMachine() override;
};

} // namespace llvm

#endif
