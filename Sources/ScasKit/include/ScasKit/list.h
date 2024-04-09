#pragma once

typedef struct list *list_t;

struct list {
    unsigned int capacity;
    unsigned int length;
    void **items;
};

list_t create_list();
void list_free(list_t list);
void list_add(list_t list, void *item);
void list_del(list_t list, unsigned int index);
void list_cat(list_t list, list_t source);
