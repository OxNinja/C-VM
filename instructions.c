#include "main.h"
#include "stack.h"
#include "instructions.h"

void my_mov(Registers *regs, Stack *stack, int shellcode) {
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

void my_add(Registers *regs, Stack *stack, int shellcode) {
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

void my_sub(Registers *regs, Stack *stack, int shellcode) {
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

void my_jmp(Registers *regs, Stack *stack, int shellcode) {}
void my_call(Registers *regs, Stack *stack, int shellcode) {}

void my_exit(Registers *regs, Stack *stack, int shellcode) { exit(regs->a); }

void my_cmp(Registers *regs, Stack *stack, int shellcode) {
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

void my_push(Registers *regs, Stack *stack, int shellcode) {
  int value = shellcode & 0x00ffffff;
  (*stack->stack_pointer = &value;
  stack_inc(stack);
}

void my_pop(Registers *regs, Stack *stack, int shellcode) {
  int target_reg = (shellcode & 0x00f00000) >> 0x14;
  stack_dec(stack);
  int value = *stack->stack_pointer;
  regs->registers[target_reg] = value;
}
