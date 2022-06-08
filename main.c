#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define FLAG_ZERO 0x10000000

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
void set_zero_flag(Registers *regs, int cmp);
void emulate(Registers *regs, int shellcode);
void my_mov(Registers *regs, int shellcode);
void my_add(Registers *regs, int shellcode);
void my_sub(Registers *regs, int shellcode);
void my_jmp(Registers *regs, int shellcode);
void my_call(Registers *regs, int shellcode);
void my_exit(Registers *regs, int shellcode);
void my_cmp(Registers *regs, int shellcode);
void my_push(Registers *regs, int shellcode);
void my_pop(Registers *regs, int shellcode);

int main(void) {
  // init the struct
  Registers regs;
  // setup the registers' array
  setup_registers(&regs);

  // set everything to 0
  reset_registers(&regs);

  // mov a, 0x45
  emulate(&regs, 0x1100045);
  // exit(a)
  emulate(&regs, 0x8000000);

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

void set_zero_flag(Registers *regs, int cmp) {
  if (cmp == TRUE) {
    regs->flags |= FLAG_ZERO;
  } else if (cmp == FALSE) {
    regs->flags |= FLAG_ZERO;
    regs->flags ^= FLAG_ZERO;
  } else {
    except("Invalid valur for set_zero_flag (cmp is neither of TRUE or FALSE)");
  }
}

void emulate(Registers *regs, int shellcode) {
  int opcode = (shellcode & 0xff000000) >> 0x18;

  // instructions is an array of pointers of function
  // each index points to the according function corresponding to the opcode
  // it is very easy to change the opcode for a certain function
  void (*instructions[10])(Registers *, int);
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

  (*instructions[opcode])(regs, shellcode);
}

void my_mov(Registers *regs, int shellcode) {
  int is_reg1 = (shellcode & 0x00f00000) >> 0x14;
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

void my_add(Registers *regs, int shellcode) {
  int is_reg1 = (shellcode & 0x00f00000) >> 0x14;
  if (is_reg1 == 0x1) {
    // get index of target reg
    int target_reg = (shellcode & 0x000f0000) >> 0x10;
    // get value to add
    int is_reg2 = (shellcode & 0x0000f000) >> 0xc;
    // get value
    int value = (shellcode & 0x00000fff);
    // if source is a register and not a value
    if (is_reg2 == 0x1) {
      int source_reg = value >> 0x8;
      value = *regs->registers[source_reg];
    }

    // finally, add the value into the register
    *regs->registers[target_reg] += value;

  } else {
    except("Invalid value for add (arg a is not a register)");
  }
}

void my_sub(Registers *regs, int shellcode) {
  int is_reg1 = (shellcode & 0x00f00000) >> 0x14;
  if (is_reg1 == 0x1) {
    // get index of target reg
    int target_reg = (shellcode & 0x000f0000) >> 0x10;
    // get value to sub
    int is_reg2 = (shellcode & 0x0000f000) >> 0xc;
    // get value
    int value = (shellcode & 0x00000fff);
    // if source is a register and not a value
    if (is_reg2 == 0x1) {
      int source_reg = value >> 0x8;
      value = *regs->registers[source_reg];
    }

    // finally, sub the value into the register
    *regs->registers[target_reg] -= value;

  } else {
    except("Invalid value for sub (arg a is not a register)");
  }
}

void my_jmp(Registers *regs, int shellcode) {}
void my_call(Registers *regs, int shellcode) {}

void my_exit(Registers *regs, int shellcode) { exit(regs->a); }

void my_cmp(Registers *regs, int shellcode) {
  int is_reg1 = (shellcode & 0x00f00000) >> 0x14;
  if (is_reg1 == 0x1) {
    // get index of target reg
    int target_reg = (shellcode & 0x000f0000) >> 0x10;
    // get value to cmp
    int is_reg2 = (shellcode & 0x0000f000) >> 0xc;
    // get cmp value
    int value = (shellcode & 0x00000fff);
    // if source is a register and not a value
    if (is_reg2 == 0x1) {
      int source_reg = value >> 0x8;
      value = *regs->registers[source_reg];
    }

    // finally, cmp the value with the register's and set the flags
    if (*regs->registers[target_reg] == value) {
      set_zero_flag(regs, TRUE);
    } else {
      set_zero_flag(regs, FALSE);
    }

  } else {
    except("Invalid value for mov (arg a is not a register)");
  }
}

void my_push(Registers *regs, int shellcode) {}
void my_pop(Registers *regs, int shellcode) {}
