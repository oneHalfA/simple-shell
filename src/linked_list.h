#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

#define foreach(h) for (; h; h = h->next)

void show_list(list *head);
list *create_node(char *data, size_t length);
list* add_list(list *head, list *new_node);
void free_list(list *head);


#endif
