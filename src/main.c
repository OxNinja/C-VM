#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

int main(void) {
  // init VM
  //   init stack
  stack *stack = stack_init();
  //   init heap?
  //   init registers
  registers *regs = registers_init(stack);

  registers_print(regs);

  // emulate some instructions
  vm_emulate(regs, stack, 0x2cafeff);
  stack_print(stack);

  vm_emulate(regs, stack, 0x9300000);
  stack_print(stack);
  registers_print(regs);

  return 0;
}
