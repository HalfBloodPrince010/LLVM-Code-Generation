//===-- ASAHIMCTargetDesc.h - ASAHI Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/// Provides ASAHI specific target descriptions.
//
//===----------------------------------------------------------------------===//
//

#ifndef LLVM_LIB_TARGET_ASAHI_MCTARGETDESC_ASAHIMCTARGETDESC_H
#define LLVM_LIB_TARGET_ASAHI_MCTARGETDESC_ASAHIMCTARGETDESC_H

#include <cstdint> // For int16_t and so on used in the .inc files.

// Defines symbolic names for ASAHI registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "ASAHIGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "ASAHIGenSubtargetInfo.inc"

#endif