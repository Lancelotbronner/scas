#pragma once

#include <ScasKit/objects.h>

object_t *merge_objects(list_t objects);
area_t *get_area_by_name(object_t *object, char *name);
bool merge_areas(object_t *merged, object_t *source);
void relocate_area(area_t *area, uint64_t address, bool immediates);
