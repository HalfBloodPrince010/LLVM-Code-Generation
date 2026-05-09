//==-- ASAHIInstPrinter.cpp - Convert ASAHI MCInst to assembly syntax --==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an ASAHI MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "ASAHIInstPrinter.h"

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#define GET_INSTRUCTION_NAME
#define PRINT_ALIAS_INSTR
#include "ASAHIGenAsmWriter.inc"

ASAHIInstPrinter::ASAHIInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                                   const MCRegisterInfo &MRI)
    : MCInstPrinter(MAI, MII, MRI) {}

void ASAHIInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                 StringRef Annot, const MCSubtargetInfo &STI,
                                 raw_ostream &O) {
    if(!PrintAliases || !printAliasInstr(MI, Address, O)) {
        printInstruction(MI, Address, O);
    }

    printAnnotation(O, Annot);
}

void ASAHIInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O) {
    const MCOperand &Op = MI->getOperand(OpNo);

    if(Op.isReg()) {
        unsigned Reg = Op.getReg();
        printRegName(O, Reg);
    } else if (Op.isImm()) {
        printImm(MI, OpNo, O);
    }  else {
        assert(Op.isExpr() && "unknown operand kind in printOperand");
        Op.getExpr()->print(O, &MAI);
    }                
}

void ASAHIInstPrinter::printImm(const MCInst *MI, unsigned OpNo, raw_ostream &O) {
    const MCOperand &Op = MI->getOperand(OpNo);
    markup(O, Markup::Immediate) << "#" << formatImm(Op.getImm());
}

void ASAHIInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) {
  markup(OS, Markup::Register) << getRegisterName(Reg);
}
