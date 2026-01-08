//===--- ASAHI.h - Declare ASAHI target feature support -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares ASAHI TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_ASAHI_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_ASAHI_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Support/Compiler.h" // For LLVM_LIBRARY_VISIBILITY.
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {

// ASAHI class
// Clang specific TargetInfo
class LLVM_LIBRARY_VISIBILITY ASAHITargetInfo : public TargetInfo {
public:
  ASAHITargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    
    // - little-endian (lsb is at the lowest address)
    // - Pointer sizes are 16-bit (i.e., only 64KB of addressable space)
    // - Native support of 16 and 32-bit integers
    // - Alignments are:
    //     -- 32-bit for 32-bit type
    //     -- 16-bit for 16-bit type
    //     -- 8-bit for 1-bit type
    //     -- 32-bit f32 (single precision floating-point type)
    //     -- 32-bit for 32-bit vector types (e.g., <4 x i8>, <2 x i16>)
    resetDataLayout(
        // Little-endian.
        // e = little endian
        // E = big endian
        "e-"

        // Pointer size is 16-bit and the alignment matches.
        // pointer_type: pointer size (bits): ABI alignment (bits): preferred alignment (bits)
        // sizeof(void*) == 2
        // alignof(void*) == 2
        "p:16:16:16-"

        // Supports natively 16-bit and 32-bit integer.
        "n16:32-"

        // i32 are aligned on 32, i16 on 16 and i1 on 8.
        // type: ABI alignment: Preferred Alignment Type
        // i32 :  32          : 32
        // Meaning i32 occupies 32 bits
        "i32:32:32-i16:16:16-i1:8:8-"

        // f32 aligned on 32-bit.
        "f32:32:32-"
        
        // v32 aligned on 32-bit.
        // vector registers occupy 32 bits -- <2x16> or <4x8> 
        "v32:32:32"
    
    );
  }

  /// Appends the target-specific \#define values for this
  /// target set to the specified buffer.
  /// This is where Clang injects target-specific preprocessor macros.
  /// Enables to select the right code for right target
  /// #if defined(__x86_64__)
  /// ...
  /// #elif defined(__arm__)
  /// ...
  /// #else
  /// #error "Unsupported architecture"
  /// #endif
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  /// Return information about target-specific builtins for
  /// the current primary target, and info about which builtins are non-portable
  /// across the current set of primary and secondary targets.
  /// Also, useful when we define the intrincs we will define the
  /// __builtins__
  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    return std::nullopt;
  }


  /// Returns the kind of __builtin_va_list type that should be used
  /// with this target.
  BuiltinVaListKind getBuiltinVaListKind() const override {
    return CharPtrBuiltinVaList;
  }


  /// TODO: For the below methods, ignore it for now
  /// Its specific to inline assembly.
  /// Need to learn more on the GCC inline assembly
  /// How we can create GCC register alias, mapping
  /// etc.
  /// Even clobbers is a topic specific to inline assembly
  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    return false;
  }

  std::string_view getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override {
    return std::nullopt;
  }
  ArrayRef<GCCRegAlias> getGCCRegAliases() const override {
    return std::nullopt;
  }
};
} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_ASAHI_H