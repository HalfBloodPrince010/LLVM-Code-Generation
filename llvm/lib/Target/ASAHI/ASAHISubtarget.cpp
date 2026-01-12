//===- ASAHISubtarget.cpp - ASAHI Subtarget Information ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the ASAHI specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//
#include "ASAHISubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

// Pin the vtable to this file.
void ASAHISubtarget::anchor() {}


/*
High level understanding?

Subtarget is applied here at function level because, how
we generated machine code might differ, for instance

define void @foo() #0
attributes #0 = { "target-cpu"="generic" "target-features"="+mul" }

define void @bar() #1
attributes #1 = { "target-cpu"="generic" "target-features"="-mul" }

foo func here support multiplication feature
but, bar doesn't

We need this for -O1..-O2 level optimizations

What do we do if multiplication is not supported?
SHIFT + ADD? 
This is answered by TargetLowering. (TLInfo)

 -O1/-O2, LLVM runs target-aware optimizations

Example: turning a multiply into shifts/adds.

On a CPU with a mul, x * 3 might stay a multiply.
On a CPU without mul, it should become x + (x << 1).
*/
ASAHISubtarget::ASAHISubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : TargetSubtargetInfo(TT, CPU, /*TuneCPU=*/"", FS, /*PN=*/{}, /*PF=*/{},
                          /*PD=*/{},
                          /*WPR=*/nullptr,
                          /*WL=*/nullptr,
                          /*RA=*/nullptr, /*IS=*/nullptr,
                          /*OC=*/nullptr, /*FP=*/nullptr),
      TLInfo(TM) {}
