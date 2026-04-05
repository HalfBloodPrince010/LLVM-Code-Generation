//===-- MCTargetDesc/ASAHIMCAsmInfo.h - ASAHI MCAsm Interface ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/// Declaration of the ASAHI MCAsmInfos.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_ASAHI_MCTARGETDESC_ASAHIMCASMINFO_H
#define LLVM_LIB_TARGET_ASAHI_MCTARGETDESC_ASAHIMCASMINFO_H


#include "llvm/MC/MCAsmInfoDarwin.h"
#include "llvm/MC/MCAsmInfoELF.h"
namespace llvm {

class Triple;

class ASAHIMCAsmInfoELF : public MCAsmInfoELF {
public:
    explicit ASAHIMCAsmInfoELF(const Triple &TT, const MCTargetOptions &Options);
}

class ASAHIMCAsmInfoDarwin : public MCAsmInfoDarwin {
public:
    explicit ASAHIMCAsmInfoDarwin(const Triple &TT, const MCTargetOptions &Options);
}

} // namespace LLVM

#endif // LLVM_LIB_TARGET_ASAHI_MCTARGETDESC_ASAHIMCASMINFO_H