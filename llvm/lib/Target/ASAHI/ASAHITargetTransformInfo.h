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


#ifndef LLVM_LIB_ASAHI_ASAHITARGETTRANSFORMINFO_H
#define LLVM_LIB_ASAHI_ASAHITARGETRANSFORMINFO_H

#include "ASAHISubtarget.h"
#include "ASAHITargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"

namespace llvm {

class ASAHITTIImpl: public BasicTTIImplBase<ASAHITTIImpl> {
  using BaseT = BasicTTIImplBase<ASAHITTIImpl>;
  using TTI = TargetTransformInfo;

  friend BaseT;

  const ASAHISubtarget &ST;
  const ASAHITargetLowering &TLI;

  const ASAHISubtarget *getST() const { return &ST; }
  const ASAHITargetLowering *getTLI() const { return &TLI; }

public:
  explicit ASAHITTIImpl(const ASAHITargetMachine *TM, const Function &F)
      : BaseT(TM, F.getDataLayout()), ST(*TM->getSubtargetImpl(F)),
        TLI(*ST.getTargetLowering()) {}
    
  /// \name Vector TTI Implementation
  /// {@
  unsigned getLoadVectorFactor(unsigned VF, unsigned LoadSize,
                               unsigned ChainSizeInBytes,
                               VectorType *VecTy) const;

  ///@}

  InstructionCost getIntrinsicInstrCost(const IntrinsicCostAttributes &ICA, TTI::TargetCostKind CostKind);
};
} // end namespace llvm

#endif // LLVM_LIB_ASAHI_ASAHITARGETRANSFORMINFO_H