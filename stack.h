#ifndef VM_STACK_HEADER
#define VM_STACK_HEADER

typedef struct Stack {
  // LIFO stack

  // max size of the stack
  int max_size;

  // pointer to the growing stack
  void *stack, *stack_end, *stack_pointer;
  
} Stack;

void setup_stack(Stack *stack);
void print_stack(Stack *stack);
void stack_inc(Stack *stack);
void stack_dec(Stack *stack);

#endif
