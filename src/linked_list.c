#include "linked_list.h"

list *create_node(char *data, size_t length) {
  list *tmp_node = NULL;
  tmp_node = (list *)calloc(1, sizeof(list));
  tmp_node->next = NULL;
  tmp_node->data = (void *)calloc(length + 1, sizeof(char));
  char *str_data = (char *)tmp_node->data;
  strcpy(str_data, data);

  return tmp_node;
}

void add_list(list *head, list *new_node) {
  list *tmp = head;
  for (; tmp->next; tmp = tmp->next)
    ;
  tmp->next = new_node;
}

void show_list(list *head) {
  list *n = head;

  for (; n; n = n->next)
    printf("Data: %s\n", (char *)n->data);
}

void free_list(list *head) {
  list *curr = NULL;
  while (head) {
    curr = head;
    head = head->next;
    free(curr->data);
    free(curr);
  }
}
