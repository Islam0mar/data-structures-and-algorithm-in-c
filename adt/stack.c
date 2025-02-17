#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
struct stack_tag;
/* FIXME: Replace int with required type */
typedef int element_type;
typedef struct stack_tag* stack;

stack stack_create();

void stack_destroy(stack* s);

element_type stack_top(stack s);

void stack_pop(stack s);

void stack_push(stack s, element_type e);

int stack_size(stack s);

int stack_is_empty(stack s);

struct stack_tag {
  element_type data[SIZE];
  int tos;
};

static void fatal_error(const char* errmsg) {
  fprintf(stderr, "%s\n", errmsg);
  exit(1);
}

stack stack_create() {
  stack s = (stack)malloc(sizeof(struct stack_tag));
  if (s == NULL) fatal_error("out of space");
  s->tos = -1;
  return s;
}

void stack_destroy(stack* sptr) {
  if (*sptr != NULL) free(*sptr);
  *sptr = NULL;
}

element_type stack_top(stack s) { return s->data[s->tos]; }

void stack_pop(stack s) {
  if (s->tos > -1) {
    s->tos -= 1;
  }
}

void stack_push(stack s, element_type e) {
  if (s->tos < SIZE - 1) {
    s->tos++;
    s->data[s->tos] = e;
  } else {
    fatal_error("stack overflow");
  }
}

int stack_size(stack s) { return s->tos + 1; }

int stack_is_empty(stack s) { return s->tos == -1; }
