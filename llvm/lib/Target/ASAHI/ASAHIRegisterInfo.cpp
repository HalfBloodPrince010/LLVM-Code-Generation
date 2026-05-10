//===-- ASAHIRegisterInfo.cpp - ASAHI Register Information ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the ASAHI implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "ASAHIRegisterInfo.h"
#include "ASAHIFrameLowering.h"
#include "MCTargetDesc/ASAHIMCTargetDesc.h" // For the enum of the regclasses.
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "ASAHIGenRegisterInfo.inc"
using namespace llvm;

ASAHIRegisterInfo::ASAHIRegisterInfo() : ASAHIGenRegisterInfo(Register()) {}

const MCPhysReg *
ASAHIRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return nullptr;
}

BitVector ASAHIRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}
bool ASAHIRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  return false;
}

Register ASAHIRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Register();
}