//===-- ASAHIInstrInfo.cpp - ASAHI Instruction Information ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the ASAHI implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "ASAHIInstrInfo.h"
#include "ASAHI.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/Support/ErrorHandling.h"
#include <cassert>
#include <iterator>

#define GET_INSTRINFO_CTOR_DTOR
#include "ASAHIGenInstrInfo.inc"

using namespace llvm;

ASAHIInstrInfo::ASAHIInstrInfo() : ASAHIGenInstrInfo() {}