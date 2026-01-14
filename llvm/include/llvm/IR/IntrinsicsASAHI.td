//===- IntrinsicsASAHI.td - Defines ASAHI intrinsics -------*- tablegen -*-===//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines all of the ASAHI-specific intrinsics.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Definitions for all ASAHI intrinsics.
//
// All ASAHI target intrinsics starts with "llvm.asahi."

let TargetPrefix = "asahi" in {
    def int_asahi_widening_smul :
    Intrinsic<[llvm_i32_ty], [llvm_i16_ty, llvm_i16_ty]>;
    def int_asahi_widening_umul :
    Intrinsic<[llvm_i32_ty], [llvm_i16_ty, llvm_i16_ty]>;
} // end TargetPrefix = "asahi"