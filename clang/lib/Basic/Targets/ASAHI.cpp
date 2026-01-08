//===--- ASAHI.cpp - Implement ASAHI target feature support -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements ASAHI TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Targets/ASAHI.h"
#include "clang/Basic/MacroBuilder.h"


using namespace clang;
using namespace clang::targets;

void ASAHITargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  Builder.defineMacro("__ASAHI__", "1");
}
