#ifndef VM_REGISTERS_HEADER
#define VM_REGISTERS_HEADER

#include "stack.h"

typedef struct Registers {
  // common operations registers
  int a, b, c, d;

  // array to work with when manipulating registers' indexes
  // each element will point to the address of the correspponding register
  // see `setup_registers()` for more details
  int *registers[4];

  // stack registers
  void *sb, *sp;

  // flags are stored in one integer, using masks to extract them
  // remainder, zero (cmp)
  int flags;
} Registers;

void setup_registers(Registers *regs);
void print_registers(Registers *regs);
void reset_registers(Registers *regs);
void set_zero_flag(Registers *regs, int cmp);
void set_stack_registers(Registers *regs, Stack *stack);

#endif
