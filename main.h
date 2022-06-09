#ifndef VM_MAIN_HEADER
#define VM_MAIN_HEADER

#include <stdlib.h>
#include <stdio.h>

#include "registers.h"

#define TRUE 1
#define FALSE 0
#define STACK_UNIT sizeof(void *)
#define FLAG_ZERO 0x10000000

#define except(msg)                                                            \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)


void emulate(Registers *regs, Stack *stack, int shellcode);

#endif
