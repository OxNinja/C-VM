#include "main.h"
#include "registers.h"
#include "stack.h"

void setup_registers(Registers *regs) {
  // each element of the array points to the corresponding register's address
  regs->registers[0] = &regs->a;
  regs->registers[1] = &regs->b;
  regs->registers[2] = &regs->c;
  regs->registers[3] = &regs->d;
}

void print_registers(Registers *regs) {
  printf("=== Registers: ===\n");
  printf("a: 0x%x\n", regs->a);
  printf("b: 0x%x\n", regs->b);
  printf("c: 0x%x\n", regs->c);
  printf("d: 0x%x\n", regs->d);
  printf("flags: 0x%x\n", regs->flags);
  printf("=== Stack: ===\n");
  printf("sb: %p\n", regs->sb);
  printf("sp: %p\n", regs->sp);
}

void reset_registers(Registers *regs) {
  regs->a = 0;
  regs->b = 0;
  regs->c = 0;
  regs->d = 0;
  regs->flags = 0;
}

void set_stack_registers(Registers *regs, Stack *stack) {
  regs->sb = stack->stack;
  regs->sp = stack->stack_pointer;
}

void set_zero_flag(Registers *regs, int cmp) {
  if (cmp == TRUE) {
    regs->flags |= FLAG_ZERO;
  } else if (cmp == FALSE) {
    regs->flags |= FLAG_ZERO;
    regs->flags ^= FLAG_ZERO;
  } else {
    except("Invalid value for set_zero_flag (cmp is neither of TRUE or FALSE)");
  }
}
