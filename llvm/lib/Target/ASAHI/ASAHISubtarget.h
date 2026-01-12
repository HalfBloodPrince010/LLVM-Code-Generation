//===- ASAHISubtarget.h - Define Subtarget for the ASAHI ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the ASAHI specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ASAHI_ASAHISUBTARGET_H
#define LLVM_LIB_TARGET_ASAHI_ASAHISUBTARGET_H

#include "ASAHIISelLowering.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

namespace llvm {

class TargetMachine;
class Triple;

class ASAHISubtarget: public TargetSubtargetInfo {
    virtual void anchor();
    ASAHITargetLowering TLInfo;

public:
    ASAHISubtarget(const Triple &TT, StringRef CPU, StringRef FS, const TargetMachine &TM);
    const ASAHITargetLowering *getTargetLowering() const override {
        return &TLInfo;
    }
};
}

#endif
