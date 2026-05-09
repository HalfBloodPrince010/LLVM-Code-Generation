//===-- ASAHIRegisterInfo.td - Descr the ASAHI reginfo ----*- tablegen -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Register description of the ASAHI target.
//
// The register hierarchy looks like:
//        +-----------+-----+-----+
// 32-bit |  d0 |  d1 |  d2 |  d3 |
//        +--+--+--+--+--+--+--+--+
// 16-bit |r0|r1|r2|r3|r4|r5|r6|r7|
//        +--+--+--+--+--+--+--+--+
//===----------------------------------------------------------------------===//

let Namespace = "ASAHI" in {

class ASAHIReg<bits<16> enc, string name, list<Register> subregs = []>: Register<name> {
    let HWEncoding =  enc;
    let SubRegs = subregs;
    // When the subregs are specified, they cover the full register.
    // Note: Remember that !empty means the function empty, not "not empty".
    let CoveredBySubRegs = !if(!empty(subregs), false, true);
}

// Subreg definitions
def sub_low16 : SubRegIndex<16>;
def sub_high16 : SubRegIndex<16, 16>;

// Register definitions.
def R0 : ASAHIReg<0, "r0">;
def R1 : ASAHIReg<1, "r1">;
def R2 : ASAHIReg<2, "r2">;
def R3 : ASAHIReg<3, "r3">;
def R4 : ASAHIReg<4, "r4">;
def R5 : ASAHIReg<5, "r5">;
def R6 : ASAHIReg<6, "r6">;
def R7 : ASAHIReg<7, "r7">;

let SubRegIndices = [sub_low16, sub_high16] in {
  def D0 : ASAHIReg<0, "d0", [R0, R1]>;
  def D1 : ASAHIReg<1, "d1", [R2, R3]>;
  def D2 : ASAHIReg<2, "d2", [R4, R5]>;
  def D3 : ASAHIReg<3, "d3", [R6, R7]>;
}

// Register Classes
// <namespace, list of regTypes, alignment, list of registers>
def GPR16 : RegisterClass<"ASAHI", [i16], 16, (sequence "R%u", 0, 7)>;
def GPR32 : RegisterClass<"ASAHI", [i32], 32, (sequence "D%u", 0, 3)>;
} // end namespace ASAHI