#pragma once

typedef struct {
	int capacity;
	int length;
	void **items;
} stack_s;

stack_s *create_stack();
void stack_free(stack_s *stack);
void stack_push(stack_s *stack, void *item);
void *stack_pop(stack_s *stack);
void *stack_peek(stack_s *stack);
void stack_shrink_to_fit(stack_s *stack);

#define STACK_GROWTH_RATE 16
