// RUN: llvm-mc -triple=asahi %s -o - | FileCheck %s

// Check that we can parse and print back our only instruction.
// CHECK: addi16 r0, r1, r3
addi16 r0, r1, r3
