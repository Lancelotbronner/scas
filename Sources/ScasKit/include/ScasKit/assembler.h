#pragma once

#include <stdbool.h>

#include "list.h"
#include "stack.h"
#include "objects.h"

typedef struct {
	list_t include_path;
	list_t errors;
	list_t warnings;
	list_t macros;
} assembler_settings_t;

typedef struct {
	char *name;
	list_t/* char * */ macro_lines;
	list_t/* char * */ parameters;
} macro_t;

struct assembler_state {
	object_t *object;
	area_t *current_area;
	stack_s *source_map_stack;
	stack_s *file_stack;
	stack_s *file_name_stack;
	stack_s *line_number_stack;
	list_t errors;
	list_t warnings;
	list_t extra_lines;
	bool expanding_macro;
	char *line;
	int column;
	uint8_t *instruction_buffer;
	stack_s *if_stack;
	list_t equates;
	list_t macros;
	macro_t *current_macro;
	int nolist;
	uint64_t PC;
	char *last_global_label;
	assembler_settings_t *settings;
	macro_t *most_recent_macro;
	bool auto_source_maps;
	uint64_t last_relative_label;
};

object_t *assemble(FILE *file, const char *file_name, assembler_settings_t *settings);
void transform_local_labels(tokenized_expression_t *expression, const char *last_global_label);
void transform_relative_labels(tokenized_expression_t *expression, int last_relative_label, const char *const file_name);
void macro_free(macro_t *macro);
