#ifndef HEADER_VM
#define HEADER_VM

#include <stdlib.h>
#include <stdio.h>

/* Stack */

typedef struct stack_node {
  // Chained list
  struct stack_node *prev;
  struct stack_node *next;
  // Void pointer for values
  // each stack node will have a pointer towards the target value
  void *val;
} stack_node;

typedef struct stack {
  // Pointers to first and last elements
  stack_node *first;
  stack_node *last;
} stack;

stack_node * stack_node_init(void) {
  // Init stack_node on heap
  stack_node *p = (stack_node *) calloc(1, sizeof(stack_node));
  p->prev = NULL;
  p->next = NULL;
  p->val = NULL;

  return p;
}

stack * stack_init(void) {
  // Init stack on the heap
  stack *p = (stack *) calloc(1, sizeof(stack));
  // Init the stack with one empty node
  // TODO: find a better way?
  stack_node *n = stack_node_init();
  int i = 0;
  n->val = &i;

  p->first = n;
  p->last = n;

  return p;
}

void stack_push(stack *stack, void *val) {
  // New node to push
  stack_node *n = stack_node_init();
  n->val = val;

  // Change last node to new node
  stack_node *last = stack->last;
  n->prev = last;
  last->next = n;
  stack->last = n;
}

void stack_pop(stack *stack) {
  // Get last and second-last nodes
  stack_node *last = stack->last;
  stack_node *slast = last->prev;

  slast->next = NULL;
  stack->last = slast;

  free(last);
}

void stack_print(stack *stack) {
  printf("=====\nStack (%p)\nbase: %p\ntop: %p\n", stack, stack->first, stack->last);
  stack_node *n = stack->first;
  while(n != NULL) {
    int val = *(int *) n->val;
    printf("----- (%p)\nprev: %p\nval: %p -> 0x%x\nnext: %p\n", n, n->prev, n->val, val, n->next);
    n = n->next;
  }
  printf("=====\n");
}

/* Heap */

/* Registers */

typedef struct registers {
  // Common registers
  int a, b, c, d;

  // Stack-related registers
  stack_node *sb;
  stack_node *sp;

  // Flags
  int flags;
} registers;

registers * registers_init(stack *stack) {
  // Init regsiters on the heap
  registers *p = (registers *) calloc(1, sizeof(registers));
  // Set all registers to 0
  p->a = 0;
  p->b = 0;
  p->c = 0;
  p->d = 0;
  p->flags = 0;

  p->sb = stack->first;
  p->sp = p->sb;

  return p;
}

void registers_print(registers *regs) {
  printf("=====\nRegisters (%p)\na: 0x%x\nb: 0x%x\nc: 0x%x\nd: 0x%x\nflags: 0x%x\n-----\nsb: %p\nsp: %p\n=====\n", regs, regs->a, regs->b, regs->c, regs->d, regs->flags, regs->sb, regs->sp);
}


/* Instructions */

#endif // !HEADER_VM
