//===-- ASAHIISelLowering.cpp - ASAHI DAG Lowering Implementation -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the interfaces that ASAHI uses to lower LLVM code
// into a selection DAG.
//
//===----------------------------------------------------------------------===//

#include "ASAHIISelLowering.h"
#include "ASAHISubtarget.h"
#include "ASAHITargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "asahi-lowering"

/*
Target Lowering answers

- Which types/ops are legal?? (is i64 legal operation? is mul a legal operation? Subtarget calls TargetLowering for these things)
- How to expand illegal things?? (e.g., i64 add becomes two i32 adds with carry, if mul is illegal, then we can expand it to shl + add)
*/
ASAHITargetLowering::ASAHITargetLowering(const TargetMachine &TM)
                : TargetLowering(TM) {}
