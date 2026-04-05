//===-- ASAHITargetObjectFile.h - ASAHI Object Info -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//


#ifndef LLVM_LIB_TARGET_ASAHI_ASAHITARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_ASAHI_ASAHITARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

/// This implementation is used for ASAHI ELF targets (Linux in particular).
class ASAHI_ELFTargetObjectFile : public TargetLoweringObjectFileELF {
public:
    ASAHI_ELFTargetObjectFile();
}

/// This implementation is used for ASAHI Darwin targets.
class ASAHI_MachoTargetObjectFile : public TargetLoweringObjectFileMachO {
public:
    ASAHI_MachoTargetObjectFile();
}

} // llvm namespace

#endif // LLVM_LIB_TARGET_ASAHI_ASAHITARGETOBJECTFILE_H