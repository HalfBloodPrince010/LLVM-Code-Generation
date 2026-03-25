//==- ASAHITargetTransformInfo.cpp - ASAHI specific TTI pass -*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
/// \file
/// This file implements a TargetTransformInfo analysis pass specific to the
/// ASAHI target machine. It uses the target's detailed information to provide
/// more precise answers to certain TTI queries (Eg: what's the supported vector shape/size), 
/// while letting the target independent and default TTI implementations handle the rest.
///
//===----------------------------------------------------------------------===//


#include "ASAHITargetTransformInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/IntrinsicsASAHI.h"

using namespace llvm;

#define DEBUG_TYPE "asahitti"

unsigned ASAHITTIImpl::getLoadVectorFactor(unsigned VF, unsigned LoadSize,
                               unsigned ChainSizeInBytes,
                               VectorType *VecTy) const {
  // We support <2 x i16> loads
  unsigned ElemSize = VecTy->getScalarSizeInBits();

  if(ElemSize != 16) {
    return 0;
  }

  return std::min(VF, 2u);
};

InstructionCost ASAHITTIImpl::getIntrinsicInstrCost(const IntrinsicCostAttributes &ICA, TTI::TargetCostKind CostKind) {
    // the signed extension / handling needed for widening_smul is modeled as more expensive 
    // than the unsigned case or a regular instruction
    // For code size, though, this is the same.
    // For Latency (num of instruction cycles) its more.
    if(CostKind != TargetTransformInfo::TCK_CodeSize &&
      ICA.getID() == Intrinsic::asahi_widening_smul) {
        return TargetTransformInfo::TCC_Expensive;
    }

    return BaseT::getIntrinsicInstrCost(ICA, CostKind);
}
