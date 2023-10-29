#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

int main(void) {
  // init VM
  //   init stack
  stack *stack = stack_init();
  stack_print(stack);
  //   init heap?
  //   init registers
  registers *regs = registers_init(stack);
  registers_print(regs);

  int i = 4;
  void *val = &i;
  stack_push(stack, val);

  int a = 5;
  stack_push(stack, &a);
  stack_print(stack);

  stack_pop(stack);
  stack_print(stack);

  // emulate some instructions

  return 0;
}
