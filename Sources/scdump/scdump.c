#include <string.h>
#include <ScasKit/list.h>

struct {
	list_t input_files;
	char *area;
	int dump_code;
	int dump_private_symbols;
	int dump_public_symbols;
	int dump_references;
	int dump_machine_code;
} runtime;

void init_runtime() {
	runtime.input_files = create_list();
	runtime.area = NULL;
	runtime.dump_code = 0;
	runtime.dump_private_symbols = 0;
	runtime.dump_public_symbols = 0;
	runtime.dump_references = 0;
	runtime.dump_machine_code = 0;
}

bool parse_arguments(int argc, char **argv) {
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-' && argv[i][1] != '\0') {
			if (strcmp("-i", argv[i]) == 0 || strcmp("--input", argv[i]) == 0) {
				list_add(runtime.input_files, argv[++i]);
			} else if (strcmp("-a", argv[i]) == 0 || strcmp("--area", argv[i]) == 0) {
				runtime.area = argv[++i];
			} else if (strcmp("-c", argv[i]) == 0 || strcmp("--code", argv[i]) == 0) {
				runtime.dump_code = 1;
			} else if (strcmp("-p", argv[i]) == 0 || strcmp("--private-symbols", argv[i]) == 0) {
				runtime.dump_private_symbols = 1;
			} else if (strcmp("-s", argv[i]) == 0 || strcmp("--symbols", argv[i]) == 0) {
				runtime.dump_public_symbols = 1;
			} else if (strcmp("-r", argv[i]) == 0 || strcmp("--references", argv[i]) == 0) {
				runtime.dump_references = 1;
			} else if (strcmp("-x", argv[i]) == 0 || strcmp("--machine-code", argv[i]) == 0) {
				runtime.dump_machine_code = 1;
			} else {
				scas_log(L_ERROR, "Invalid option %s", argv[i]);
				return false;
			}
		} else {
			list_add(runtime.input_files, argv[i]);
		}
	}
	return true;
}

symbol_t *find_label(uint64_t address, area_t *area) {
	for (unsigned int i = 0; i < area->symbols->length; ++i) {
		symbol_t *sym = area->symbols->items[i];
		if (sym->type == SYMBOL_LABEL) {
			if (sym->value == address) {
				return sym;
			}
		}
	}
	return NULL;
}

void dump_area(area_t *a) {
	scas_log(L_INFO, "Area '%s'", a->name);
	if (runtime.dump_code) {
		for (unsigned int i = 0; i < a->source_map->length; ++i) {
			source_map_t *map = a->source_map->items[i];
			scas_log(L_INFO, "Source file '%s'", map->file_name);
			scas_log_indent += 1;
			for (unsigned int j = 0; j < map->entries->length; ++j) {
				source_map_entry_t *entry = map->entries->items[j];
				symbol_t *label = find_label(entry->address, a);
				if (label) {
					scas_log(L_INFO, "[0x%04X:%02X] %s\t%s:",
							entry->address, entry->length,
							map->file_name, label->name);
				}
				scas_log(L_INFO, "[0x%04X:%02X] %s:%d\t\t%s",
						entry->address, entry->length,
						map->file_name, entry->line_number,
						entry->source_code);
			}
			scas_log_indent -= 1;
		}
	}
	if (runtime.dump_private_symbols || runtime.dump_public_symbols) {
		/* TODO: Distinguish between private/public */
		scas_log(L_INFO, "Symbols defined:");
		scas_log_indent += 1;
		for (unsigned int i = 0; i < a->symbols->length; ++i) {
			symbol_t *sym = a->symbols->items[i];
			scas_log(L_INFO, "'%s' == 0x%08X (%s)", sym->name, sym->value,
					sym->type == SYMBOL_LABEL ? "Label" : "Equate");
		}
		scas_log_indent -= 1;
	}
	if (runtime.dump_references) {
		scas_log(L_INFO, "Unresolved references:");
		for (unsigned int i = 0; i < a->late_immediates->length; ++i) {
			late_immediate_t *imm = a->late_immediates->items[i];
			printf("  [0x%04X] ", (uint16_t)imm->address);
			print_tokenized_expression(stdout, imm->expression);
			printf("\n");
		}
	}
}

area_t *find_area(const char *name, object_t *o) {
	for (unsigned int i = 0; i < o->areas->length; ++i) {
		area_t *a = o->areas->items[i];
		if (strcasecmp(a->name, name) == 0) {
			return a;
		}
	}
	return NULL;
}

int main(int argc, char **argv) {
	init_runtime();
	if (!parse_arguments(argc, argv)) {
		return 1;
	}
	scas_log_verbosity = L_INFO;
	scas_log_colorize = false;
	for (unsigned int i = 0; i < runtime.input_files->length; ++i) {
		FILE *f;
		if (strcasecmp(runtime.input_files->items[i], "-") == 0) {
			f = stdin;
		} else {
			f = fopen(runtime.input_files->items[i], "r");
		}
		if (!f) {
			scas_log(L_ERROR, "Unable to open '%s' for linking.", runtime.input_files->items[i]);
			return 1;
		}
		object_t *o = freadobj(f, runtime.input_files->items[i]);
		if (runtime.area == NULL) {
			for (unsigned int j = 0; j < o->areas->length; ++j) {
				area_t *a = o->areas->items[j];
				dump_area(a);
			}
		} else {
			area_t *a = find_area(runtime.area, o);
			if (a == NULL) {
				scas_log(L_ERROR, "Object file does not contain area '%s'.", runtime.area);
				return 1;
			}
			dump_area(a);
		}
	}
	return 0;
}
