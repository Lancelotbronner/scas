#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <ScasKit/list.h>
#include <ScasKit/errors.h>
#include <ScasKit/log.h>
#include <ScasKit/objects.h>

const char *get_error_string(error_t *error) {
	switch (error->code) {
		case ERROR_INVALID_INSTRUCTION:
			return "Invalid instruction '%s'";
		case ERROR_VALUE_TRUNCATED:
			return "Value truncated";
		case ERROR_INVALID_SYNTAX:
			return "Invalid syntax";
		case ERROR_INVALID_DIRECTIVE:
			return "Invalid directive (%s)";
		case ERROR_UNKNOWN_SYMBOL:
			return "Unknown symbol '%s'";
		case ERROR_BAD_FILE:
			return "Unable to open '%s' for reading";
		case ERROR_TRAILING_END:
			return "No matching if directive";
		case ERROR_DUPLICATE_SYMBOL:
			return "Duplicate symbol '%s'";
		default:
			return NULL;
	}
}

const char *get_warning_string(warning_t *warning) {
	switch (warning->code) {
		case WARNING_NO_EFFECT:
			return "'%s' has no effect %s";
		default:
			return NULL;
	}
}

void add_error(list_t errors, int code, size_t line_number, const char *line,
		int column, const char *file_name, ...) {
	error_t *error = malloc(sizeof(error_t));
	error->code = code;
	error->line_number = line_number;
	error->file_name = strdup(file_name);
	error->line = strdup(line);
	error->column = column;

	const char *fmt = get_error_string(error);

	va_list args;
	va_start(args, file_name);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *buf = malloc(len + 1);
	va_start(args, file_name);
	vsnprintf(buf, len + 1, fmt, args);
	va_end(args);

	error->message = buf;

	list_add(errors, error);
	scas_log(L_DEBUG, "Added error '%s' at %s:%d:%d", buf, file_name,
			line_number, column);
}

void add_warning(list_t warnings, int code, size_t line_number,
		const char *line, int column, const char *file_name, ...) {
	warning_t *warning = malloc(sizeof(warning_t));
	warning->code = code;
	warning->line_number = line_number;
	warning->file_name = strdup(file_name);
	warning->line = strdup(line);
	warning->column = column;

	const char *fmt = get_warning_string(warning);

	va_list args;
	va_start(args, file_name);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *buf = malloc(len + 1);
	va_start(args, file_name);
	vsnprintf(buf, len + 1, fmt, args);
	va_end(args);

	warning->message = buf;

	list_add(warnings, warning);
	scas_log(L_DEBUG, "Added warning '%s' at %s:%d:%d", buf, file_name,
			line_number, column);
}

/* Locates the address in the source maps provided to get the file name and line number */
void add_error_from_map(list_t errors, int code, list_t maps, uint64_t address, ...) {
	source_map_t *map;
	source_map_entry_t *entry;
	bool found = false;
	for (unsigned int i = 0; i < maps->length; ++i) {
		map = maps->items[i];
		for (unsigned int j = 0; j < map->entries->length; ++j) {
			entry = map->entries->items[j];
			if (address >= entry->address && address < entry->address + entry->length) {
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	error_t *error = malloc(sizeof(error_t));
	error->code = code;
	error->column = 0;

	const char *fmt = get_error_string(error);

	va_list args;
	va_start(args, address);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *buf = malloc(len + 1);
	va_start(args, address);
	vsnprintf(buf, len + 1, fmt, args);
	va_end(args);

	error->message = buf;
	scas_log(L_DEBUG, "Added error '%s' at:", buf);
	if (found) {
		error->line_number = entry->line_number;
		error->file_name = strdup(map->file_name);
		error->line = strdup(entry->source_code);
		for (unsigned int i = 0; i < maps->length; ++i) {
			map = maps->items[i];
			for (unsigned int j = 0; j < map->entries->length; ++j) {
				entry = map->entries->items[j];
				if (address >= entry->address && address < entry->address + entry->length) {
					scas_log(L_ERROR, "\t%s:%d:%d", map->file_name,
							entry->line_number, error->column);
				}
			}
		}
	} else {
		error->line_number = 0;
		error->file_name = NULL;
		error->line = NULL;
	}
	list_add(errors, error);
}
