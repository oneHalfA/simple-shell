#include "parse_symbol.h"
#include "linked_list.h"

void reset(str_quote_t *tmp) {
  tmp->finished = false;
  tmp->inx = 0;
  memset(tmp, 0, 128);
}

void skip_delim(char *str, int *index) {
  for (; str[*index + 1] == '\t' || str[*index + 1] == ' '; (*index)++)
    ;
}

int parse_quote(inputBuffer *buffer) {

  char *input = buffer->input;
  list *head = NULL;

  char token[MAX_BUFFER_SIZE]; // token is the final form of argument that will be added to the list.

  bool saw_d = false;
  bool saw_s = false;
  str_quote_t str;
  int index = 0;

  reset(&str);
  
  for (int i = 0; input[i]; i++) {

    // ================================================== set the str if saw SQ
    if (input[i] == SQ) {
      if (saw_d == false) {
        saw_s = !saw_s;
        if (input[i + 1] != SQ)
          str.finished = !saw_s;
      }
    } else if (input[i] == DQ) {
      if (!saw_s) {
        saw_d = !saw_d;
        if (input[i + 1] != DQ)
          str.finished = !saw_d;
      }
    }
    // ================================================== fill str
    if ((saw_s && input[i] != SQ) || (saw_d && input[i] != DQ))
      str.str_between[str.inx++] = input[i];
    else if (str.finished) {
      str.str_between[str.inx] = 0;
      token[index] = 0;
      strcat(token, str.str_between);
      index += str.inx;
      reset(&str);
    }
    // ================================================== concatenate str with token and add it to the list
    if (!saw_d && !saw_s && str.finished == false) {
      if (input[i] == '\t' || input[i] == ' ') {

        skip_delim(input, &i);
        token[index] = 0;
        head = add_list(head, create_node(token, strlen(token)));
        buffer->tc.argn++;
        index = 0;
        // print_final(token, &index);
      } else {

        if (input[i] != SQ && input[i] != DQ)
          token[index++] = input[i];
        if (!input[i + 1]) {
          token[index] = 0;
          head = add_list(head, create_node(token, strlen(token)));
          buffer->tc.argn++;
          index = 0;
        }
      }
    }
  }

  if (saw_d || saw_s) {
    return FAILED;
  }

  char **argv = NULL;
  argv = (char **)calloc(
      buffer->tc.argn + 1,
      sizeof(char *)); // The `+ 1` is for the last element of argv in execv
                       // function which it needs to be NULL.

  int i = 0;
  foreach (head) {
    argv[i] = (char *)calloc(strlen((char *)head->data), sizeof(char));
    strcpy(argv[i++], (char *)head->data);
  }
  argv[i] = NULL;
  buffer->tc.argv = argv;

  free_list(head);

  return OK;
}
