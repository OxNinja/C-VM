#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "stack.h"

void setup_stack(Stack *stack) {
  int stack_size = stack->max_size * STACK_UNIT;
  stack->stack = (int *) malloc(stack_size);
  stack->stack_base = stack->stack;
  stack->stack_end = stack->stack + stack_size;
  stack->stack_pointer = &stack->stack;
}

void print_stack(Stack *stack) {
  printf("--- Stack content ---\n");
  int stack_size = *stack->stack_pointer - stack->stack;
  for(int i = 0; i < stack_size; i += STACK_UNIT) {
    printf("[+0x%04x]: %x\n", i, *(*(stack->stack_pointer + i)));
  }
}

void stack_inc(Stack *stack) {
  stack->stack_pointer += STACK_UNIT;
}

void stack_dec(Stack *stack) {
  stack->stack_pointer -= STACK_UNIT;
}
