#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int32_t value;
  struct Node *previous;
} Node;

typedef struct Stack {
  size_t size;
  Node *top;
} Stack;

typedef enum StackError {
  OK,
  NULL_POINTER,
  ALLOCATION_FAILED,
  EMPTY_STACK
} StackError;

StackError new_stack(Stack **out);
StackError push(Stack *stack, int32_t value);
StackError pop(Stack *stack, int32_t *out);
StackError peek(Stack *stack, int32_t *out);
StackError free_stack(Stack *stack);
char *error_message_stack(StackError error);

int main(void) {
  Stack *stack;
  StackError stack_error;

  if ((stack_error = new_stack(&stack)) != OK) {
    fprintf(stderr, "could not create stack, error: %s\n",
            error_message_stack(stack_error));
    exit(EXIT_FAILURE);
  }

  for (int32_t i = 0; i < 3; ++i) {
    if ((stack_error = push(stack, i)) != OK) {
      fprintf(stderr, "could not push, error: %s\n",
              error_message_stack(stack_error));
    }
  }

  for (size_t i = 0; i < 3; ++i) {
    int32_t value;

    if ((stack_error = peek(stack, &value)) != OK) {
      fprintf(stderr, "could not peek, error: %s\n",
              error_message_stack(stack_error));
    } else {
      printf("peek: %d\n", value);
    }

    if ((stack_error = pop(stack, &value)) != OK) {
      fprintf(stderr, "could not pop, error: %s\n",
              error_message_stack(stack_error));
    } else {
      printf("pop: %d\n", value);
    }
  }

  free_stack(stack);

  return 0;
}

StackError new_stack(Stack **out) {
  if (out == NULL) {
    return NULL_POINTER;
  }

  Stack *stack = (Stack *)malloc(sizeof(Stack));
  if (stack == NULL) {
    return ALLOCATION_FAILED;
  }

  stack->size = 0;
  stack->top = NULL;

  *out = stack;

  return OK;
}

StackError push(Stack *stack, int32_t value) {
  if (stack == NULL) {
    return NULL_POINTER;
  }

  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    return ALLOCATION_FAILED;
  }

  node->value = value;
  node->previous = stack->top;

  stack->top = node;
  ++stack->size;

  return OK;
}

StackError pop(Stack *stack, int32_t *out) {
  if (stack == NULL || out == NULL) {
    return NULL_POINTER;
  }

  if (stack->size == 0) {
    return EMPTY_STACK;
  }

  Node *popped_top = stack->top;
  stack->top = popped_top->previous;
  --stack->size;

  *out = popped_top->value;
  free(popped_top);

  return OK;
}

StackError peek(Stack *stack, int32_t *out) {
  if (stack == NULL || out == NULL) {
    return NULL_POINTER;
  }

  if (stack->size == 0) {
    return EMPTY_STACK;
  }

  *out = stack->top->value;

  return OK;
}

StackError free_stack(Stack *stack) {
  if (stack == NULL) {
    return NULL_POINTER;
  }

  Node *current = stack->top;

  while (current != NULL) {
    Node *delete = current;
    current = current->previous;
    free(delete);
  }

  free(stack);

  return OK;
}

char *error_message_stack(StackError error) {
  switch (error) {
  case OK:
    return "no error";
  case NULL_POINTER:
    return "operation cannot be performed on a null pointer";
  case ALLOCATION_FAILED:
    return "could not allocate memory for operation";
  case EMPTY_STACK:
    return "operation could not be performed because stack is empty";
  default:
    return "unknown error";
  }
}
