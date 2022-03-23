#include <stdio.h>


typedef struct Registers {
  // common operations registers
  int rax, rbx, rcx, rdx;
} Registers;


int main(void) {
  Registers regs;
  Registers *rp;

  rp = &regs;

  printf("regs: %p\nrp: %p\n", &regs, rp);

  print_registers(regs);
  //reset_registers(regs);
  print_registers(regs);

  return 0;
}


void print_registers(Registers *regs) {
  printf("rax: %x\n", regs->rax);
  printf("rbx: %x\n", regs->rbx);
  printf("rcx: %x\n", regs->rcx);
  printf("rdx: %x\n", regs->rdx);
}

void reset_registers(Registers *regs) {
  regs->rax = 0;
  regs->rbx = 0;
  regs->rcx = 0;
  regs->rdx = 0;
}
