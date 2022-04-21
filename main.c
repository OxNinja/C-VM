#include <stdio.h>

typedef struct Registers {
  // common operations registers
  int a, b, c, d;
} Registers;

void print_registers(Registers *regs);
void reset_registers(Registers *regs);

int main(void) {
  Registers regs;

  print_registers(&regs);
  reset_registers(&regs);
  print_registers(&regs);

  return 0;
}

void print_registers(Registers *regs) {
  printf("=== Registers: ===\n");
  printf("a: 0x%x\n", regs->a);
  printf("b: 0x%x\n", regs->b);
  printf("c: 0x%x\n", regs->c);
  printf("d: 0x%x\n", regs->d);
}

void reset_registers(Registers *regs) {
  regs->a = 0;
  regs->b = 0;
  regs->c = 0;
  regs->d = 0;
}