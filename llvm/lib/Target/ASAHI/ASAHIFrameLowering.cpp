//===-- ASAHIFrameLowering.cpp - ASAHI Frame Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the ASAHI implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "ASAHIFrameLowering.h"
#include "ASAHIInstrInfo.h"
#include "ASAHISubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

bool ASAHIFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  return false;
}

void ASAHIFrameLowering::emitPrologue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {}

void ASAHIFrameLowering::emitEpilogue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {}