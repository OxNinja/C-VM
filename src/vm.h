#ifndef HEADER_VM
#define HEADER_VM

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define FLAG_ZERO 0x10000000

#define except(msg)                                                            \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

/* Stack */

typedef struct stack_node {
  // Chained list
  struct stack_node *prev;
  struct stack_node *next;
  // Void pointer for values
  // each stack node will have a pointer towards the target value
  int *val;
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

void stack_push(stack *stack, int *val) {
  // New node to push
  stack_node *n = stack_node_init();
  n->val = val;

  // Change last node to new node
  stack_node *last = stack->last;
  n->prev = last;
  last->next = n;
  stack->last = n;

  // TODO: update registers

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
  printf("\n=====\nStack (%p)\nbase: %p\ntop: %p\n", stack, stack->first, stack->last);
  // stack->last->val = 0 here
  stack_node *n = stack->first;
  while(n != NULL) {
    printf("----- (%p)\nprev: %p\nval: %p -> 0x%x\nnext: %p\n", n, n->prev, n->val, *n->val, n->next);
    n = n->next;
  }
  printf("=====\n");
}

/* Heap */

/* Registers */

typedef struct registers {
  // Common registers
  int a, b, c, d;

  // array to work with when manipulating registers' indexes
  // each element will point to the address of the correspponding register
  // see `registers_init()` for more details
  int *registers[4];

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

  // Set stack-related registers
  p->sb = stack->first;
  p->sp = p->sb;

  // Set the registers array
  p->registers[0] = &p->a;
  p->registers[1] = &p->b;
  p->registers[2] = &p->c;
  p->registers[3] = &p->d;

  return p;
}

void registers_print(registers *regs) {
  printf("=====\nRegisters (%p)\na: 0x%x\nb: 0x%x\nc: 0x%x\nd: 0x%x\nflags: 0x%x\n-----\nsb: %p\nsp: %p\n=====\n", regs, regs->a, regs->b, regs->c, regs->d, regs->flags, regs->sb, regs->sp);
}

/* Flags */ 

void flags_set_zero(registers *regs, int val) {
  if (val == TRUE) {
    regs->flags |= FLAG_ZERO;
  } else if (val == FALSE) {
    regs->flags |= FLAG_ZERO;
    regs->flags ^= FLAG_ZERO;
  } else {
    except("Invalid value for flags_set_zero (cmp is neither of TRUE or FALSE)");
  }
}

/* Instructions */

void vm_mov(registers *regs, stack *stack, int shellcode) {
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

void vm_add(registers *regs, stack *stack, int shellcode) {
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

void vm_sub(registers *regs, stack *stack, int shellcode) {
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

void vm_jmp(registers *regs, stack *stack, int shellcode) {}
void vm_call(registers *regs, stack *stack, int shellcode) {}

void vm_exit(registers *regs, stack *stack, int shellcode) { exit(regs->a); }

void vm_cmp(registers *regs, stack *stack, int shellcode) {
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
      flags_set_zero(regs, TRUE);
    } else {
      flags_set_zero(regs, FALSE);
    }

  } else {
    except("Invalid value for mov (arg a is not a register)");
  }
}

void vm_push(registers *regs, stack *stack, int shellcode) {
  int value = shellcode & 0x00ffffff;
  int *pointer = (int *) calloc(1, sizeof(int));
  pointer = &value;
  stack_push(stack, pointer);
}

void vm_pop(registers *regs, stack *stack, int shellcode) {
  int target_reg = (shellcode & 0x00f00000) >> 0x14;
  stack_node *n = stack->last;
  int value = *(int *) n->val;
  *regs->registers[target_reg] = value;
  stack_pop(stack);
}

void vm_emulate(registers *regs, stack *s, int shellcode) {
  int opcode = (shellcode & 0xff000000) >> 0x18;

  // instructions is an array of pointers of function
  // each index points to the according function corresponding to the opcode
  // it is very easy to change the opcode for a certain function
  void (*instructions[10])(registers *, stack *, int);
  // no opcode 0 defined for the moment
  instructions[1] = vm_mov;
  instructions[2] = vm_push;
  instructions[3] = vm_add;
  instructions[4] = vm_sub;
  instructions[5] = vm_jmp;
  instructions[6] = vm_cmp;
  instructions[7] = vm_call;
  instructions[8] = vm_exit;
  instructions[9] = vm_pop;
  // this is not optimal, as this occurs every time we want to emulate code
  // one should declare this array once for all for better performance

  (*instructions[opcode])(regs, s, shellcode);
}

#endif // !HEADER_VM
