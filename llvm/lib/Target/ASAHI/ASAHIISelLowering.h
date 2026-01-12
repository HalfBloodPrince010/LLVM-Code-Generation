//===-- ASAHIISelLowering.h - ASAHI DAG Lowering Interface --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that ASAHI uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ASAHI_ASAHIISELLOWERING_H
#define LLVM_LIB_TARGET_ASAHI_ASAHIISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class ASAHISubtarget;
class ASAHITargetMachine;

class ASAHITargetLowering: public TargetLowering {
public:
    explicit ASAHITargetLowering(const TargetMachine &TM);
};

} // llvm namespace

#endif
