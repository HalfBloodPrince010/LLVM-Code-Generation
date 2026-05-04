include "ASAHIInstrFormats.td"

def Addi16rr : ASAHIInstruction<"addi16", "$dst, $src0, $src1",
                                (outs GPR16:$dst),
                                (ins GPR16:$src0, GPR16:$src1)>