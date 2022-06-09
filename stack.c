#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "stack.h"

void setup_stack(Stack *stack) {
  int stack_size = stack->max_size * STACK_UNIT;
  stack->stack = (void *) malloc(stack_size);
  stack->stack_end = stack->stack + stack_size;
  stack->stack_pointer = stack->stack;
}

void print_stack(Stack *stack) {
  printf("stack start: %p\n", stack->stack);
  printf("stack end: %p\n", stack->stack_end);
}

void stack_inc(Stack *stack) {
  stack->stack_pointer += STACK_UNIT;
}

void stack_dec(Stack *stack) {
  stack->stack_pointer -= STACK_UNIT;
}
