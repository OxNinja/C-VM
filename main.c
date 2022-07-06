#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "instructions.h"
#include "registers.h"
#include "stack.h"

int main(void) {
  // init the stack
  Stack stack;
  // stack of 0x100 pointers max
  stack.max_size = 0x100;
  // setup the stack
  setup_stack(&stack);

  // init the registers
  Registers regs;
  // setup the registers' array
  setup_registers(&regs);
  // setup the registers
  setup_stack_registers(&regs, &stack);

  // set everything to 0
  reset_registers(&regs);

  // mov a, 0x45
  emulate(&regs, &stack, 0x1100045);
  print_registers(&regs);

  // push 0x2b
  emulate(&regs, &stack, 0x0200002b);
  print_registers(&regs);
  print_stack(&stack);

  // pop a
  emulate(&regs, &stack, 0x09000000);
  print_registers(&regs);
  print_stack(&stack);

  return 0;
}


void emulate(Registers *regs, Stack *stack, int shellcode) {
  int opcode = (shellcode & 0xff000000) >> 0x18;

  // instructions is an array of pointers of function
  // each index points to the according function corresponding to the opcode
  // it is very easy to change the opcode for a certain function
  void (*instructions[10])(Registers *, Stack *, int);
  // no opcode 0 defined for the moment
  instructions[1] = my_mov;
  instructions[2] = my_push;
  instructions[3] = my_add;
  instructions[4] = my_sub;
  instructions[5] = my_jmp;
  instructions[6] = my_cmp;
  instructions[7] = my_call;
  instructions[8] = my_exit;
  instructions[9] = my_pop;
  // this is not optimal, as this occurs every time we want to emulate code
  // one should declare this array once for all for better performance

  (*instructions[opcode])(regs, stack, shellcode);
}
