// output operand list = empty outputs, same with input
// basically (outs) ---> empty output operands
class ASAHIInstruction<string asm, string operands, dag oops = (outs), dag iops = (ins)> : Instruction<> {
    let Namespace = "ASAHI";
    let AsmString = !strconcat(asm, "\t", operands);
    let OutOperandList = oops;
    let InOperandList = iops;
}