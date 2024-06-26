#include <ScasKit/expression.h>

uint64_t operator_add(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number + right->number;
}

uint64_t operator_subtract(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number - right->number;
}

uint64_t operator_unary_plus(stack_s *stack, int *error) {
	expression_token_t *token = stack_pop(stack);
	if (token == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return token->number;
}

uint64_t operator_unary_minus(stack_s *stack, int *error) {
	expression_token_t *token = stack_pop(stack);
	if (token == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return -token->number;
}

uint64_t operator_negate(stack_s *stack, int *error) {
	expression_token_t *token = stack_pop(stack);
	if (token == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return ~token->number;
}

uint64_t operator_multiply(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number * right->number;
}

uint64_t operator_divide(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number / right->number;
}

uint64_t operator_logical_not(stack_s *stack, int *error) {
	expression_token_t *token = stack_pop(stack);
	if (token == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return !token->number;
}

uint64_t operator_modulo(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number % right->number;
}

uint64_t operator_left_shift(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number << right->number;
}

uint64_t operator_right_shift(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number >> right->number;
}

uint64_t operator_less_than(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number < right->number;
}

uint64_t operator_greater_than(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number > right->number;
}

uint64_t operator_less_than_or_equal_to(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number <= right->number;
}

uint64_t operator_greater_than_or_equal_to(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number >= right->number;
}

uint64_t operator_equal_to(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number == right->number;
}

uint64_t operator_not_equal_to(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number != right->number;
}

uint64_t operator_bitwise_and(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number & right->number;
}

uint64_t operator_bitwise_or(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number | right->number;
}

uint64_t operator_bitwise_xor(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number ^ right->number;
}

uint64_t operator_logical_and(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number && right->number;
}

uint64_t operator_logical_or(stack_s *stack, int *error) {
	expression_token_t *right = stack_pop(stack);
	expression_token_t *left = stack_pop(stack);
	if (left == NULL || right == NULL) {
		*error = EXPRESSION_BAD_SYNTAX;
		return 0;
	}
	return left->number || right->number;
}
