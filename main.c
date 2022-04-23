#include <stdio.h>
#include <stdlib.h>

#define except(msg)                                                            \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

typedef struct Registers {
  // common operations registers
  int a, b, c, d;

  // array to work with when manipulating registers' indexes
  // each element will point to the address of the correspponding register
  // see `setup_registers()` for more details
  int *registers[4];

  // opcode holder
  int op;

  // flags are stored in one integer, using masks to extract them
  // remainder, zero (cmp)
  int flags;
} Registers;

void setup_registers(Registers *regs);
void print_registers(Registers *regs);
void reset_registers(Registers *regs);
void emulate(Registers *regs, int shellcode);
void my_mov(Registers *regs, int shellcode);
void my_add(Registers *regs, int shellcode);
void my_sub(Registers *regs, int shellcode);
void my_jmp(Registers *regs, int shellcode);
void my_call(Registers *regs, int shellcode);
void my_exit(Registers *regs, int shellcode);
void my_cmp(Registers *regs, int shellcode);
void my_push(Registers *regs, int shellcode);

int main(void) {
  // init the struct
  Registers regs;
  // setup the registers' array
  setup_registers(&regs);

  // set everything to 0
  reset_registers(&regs);

  print_registers(&regs);

  emulate(&regs, 0x1110069);

  print_registers(&regs);

  emulate(&regs, 0x1130100);

  print_registers(&regs);

  return 0;
}

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
}

void reset_registers(Registers *regs) {
  regs->a = 0;
  regs->b = 0;
  regs->c = 0;
  regs->d = 0;
  regs->flags = 0;
}

void emulate(Registers *regs, int shellcode) {
  // TODO: use a struct to map the opcode to the function and call it instead of
  // a switch
  int opcode = (shellcode & 0xff000000) >> 0x18;

  // the big switch for all the opcodes
  switch (opcode) {
  case 0x1:
    my_mov(regs, shellcode);
    break;

  case 0x2:
    my_push(regs, shellcode);
    break;

  case 0x3:
    my_add(regs, shellcode);
    break;

  case 0x4:
    my_sub(regs, shellcode);
    break;

  case 0x5:
    my_jmp(regs, shellcode);
    break;

  case 0x6:
    my_cmp(regs, shellcode);
    break;

  case 0x7:
    my_call(regs, shellcode);
    break;

  case 0x8:
    my_exit(regs, shellcode);
    break;

  default:
    except("OPcode not recognized");
    break;
  }
}

void my_mov(Registers *regs, int shellcode) {
  int is_reg1 = (shellcode & 0x00f00000) >> 0x14;
  // mov reg, value
  if (is_reg1 == 0x1) {
    // get index of target reg
    int target_reg = (shellcode & 0x000f0000) >> 0x10;
    // get value to mov
    int is_reg2 = (shellcode & 0x0000f000) >> 0xc;
    // get moved value
    int value = (shellcode & 0x00000fff);
    // if source is a register and not a value
    if (is_reg2 == 0x1) {
      int source_reg = value >> 0x8;
      value = *regs->registers[source_reg];
    }

    // finally, move the value into the register
    *regs->registers[target_reg] = value;

  } else {
    except("Invalid value for mov (arg a is not a register)");
  }
}

void my_add(Registers *regs, int shellcode) {}
void my_sub(Registers *regs, int shellcode) {}
void my_jmp(Registers *regs, int shellcode) {}
void my_call(Registers *regs, int shellcode) {}
void my_exit(Registers *regs, int shellcode) {}
void my_cmp(Registers *regs, int shellcode) {}
void my_push(Registers *regs, int shellcode) {}