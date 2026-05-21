//===-- ASAHIMCTargetDesc.cpp - ASAHI Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides ASAHI specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "ASAHIInstPrinter.h"
#include "ASAHIMCTargetDesc.h"
#include "ASAHIMCAsmInfo.h"
#include "TargetInfo/ASAHITargetInfo.h" // getTheAsahiTarget
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/Support/Compiler.h" // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_SUBTARGETINFO_MC_DESC
#include "ASAHIGenSubtargetInfo.inc"

// Enable the MC-layer register-info implementation
#define GET_REGINFO_MC_DESC
#include "ASAHIGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#define GET_INSTRINFO_MC_HELPERS
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "ASAHIGenInstrInfo.inc"

static MCSubtargetInfo *
createASAHIMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
    return createASAHIMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCRegisterInfo *createASAHIMCRegisterInfo(const Triple &Triple) {
  MCRegisterInfo *X = new MCRegisterInfo();
  // Initialize all ASAHI register info,
  // and mark R7 as the return-address register.
  InitASAHIMCRegisterInfo(X, ASAHI::R7);
  return X;
}

static MCInstrInfo *createASAHIMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitASAHIMCInstrInfo(X);
  return X;
}

static MCAsmInfo *createASAHIMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TheTriple,
                                       const MCTargetOptions &Options) {
    MCAsmInfo *MAI;
    if (TheTriple.isOSBinFormatELF()) {
        MAI = new ASAHIMCAsmInfoELF(TheTriple, Options);
    } else if (TheTriple.isOSBinFormatMachO()) {
        MAI = new ASAHIMCAsmInfoDarwin(TheTriple, Options);
    } else {
        report_fatal_error("Binary format not supported");
    }

    return MAI;
}

static MCInstPrinter *createASAHIMCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
    if(SyntaxVariant == 0) {
        return new ASAHIInstPrinter(MAI, MII, MRI);
    }

    return nullptr;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeASAHITargetMC() {
    Target &TheTarget = getTheAsahiTarget();

    // Register the MC asm info.
    RegisterMCAsmInfoFn X(TheTarget, createASAHIMCAsmInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(TheTarget, createASAHIMCRegisterInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(TheTarget, createASAHIMCInstrInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(TheTarget, createASAHIMCSubtargetInfo);

    // Register the MCInst to asm printer.
    TargetRegistry::RegisterMCInstPrinter(TheTarget, createASAHIMCInstPrinter);

    // Register the MC Code Emitter
    TargetRegistry::RegisterMCCodeEmitter(TheTarget, createASAHIMCCodeEmitter);
}
