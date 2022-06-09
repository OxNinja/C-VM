#ifndef VM_INSTRUCTIONS_HEADER
#define VM_INSTRUCTIONS_HEADER

#include "registers.h"

void my_mov(Registers *regs, Stack *stack, int shellcode);
void my_add(Registers *regs, Stack *stack, int shellcode);
void my_sub(Registers *regs, Stack *stack, int shellcode);
void my_jmp(Registers *regs, Stack *stack, int shellcode);
void my_call(Registers *regs, Stack *stack, int shellcode);
void my_exit(Registers *regs, Stack *stack, int shellcode);
void my_cmp(Registers *regs, Stack *stack, int shellcode);
void my_push(Registers *regs, Stack *stack, int shellcode);
void my_pop(Registers *regs, Stack *stack, int shellcode);

#endif
