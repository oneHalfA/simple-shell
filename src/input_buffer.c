#include "input_buffer.h"

void remove_newline(char *input) {
  for (; *input != '\n'; input++)
    ;
  *input = '\0';
}

inputBuffer create_new_input_buffer(void) {
  inputBuffer tmp;
  tmp.input = (char *)calloc(MAX_BUFFER_SIZE, sizeof(char));
  tmp.input_len = 0;

  return tmp;
}

uint8_t capture_input(inputBuffer *buffer) {
  fgets(buffer->input, MAX_BUFFER_SIZE, stdin);
  remove_newline(buffer->input);

  buffer->input_len = strlen(buffer->input);
  buffer->validation = false;
  buffer->tc.argn = 0;

  if (parse_single_quote(buffer)) {
    return buffer->input_len;
  }
  char *tmp = strdup(buffer->input);
  char *token = strtok(tmp, " ");

  while (token) {
    buffer->tc.argn++;
    token = strtok(NULL, " ");
  }

  buffer->tc.argv =
      (char **)calloc(buffer->tc.argn + 1,
                      sizeof(char *)); // + 1 for last element of argv in execv
                                       // function that needs to be NULL
  strcpy(tmp, buffer->input);

  token = strtok(tmp, " ");

  for (int i = 0; i < buffer->tc.argn && token != NULL;
       i++, token = strtok(NULL, " ")) {

    buffer->tc.argv[i] = (char *)calloc(1, (size_t)strlen(token) + 1);
    strcpy(buffer->tc.argv[i], token);
  }
  buffer->tc.argv[buffer->tc.argn] = NULL;

  free(tmp);
  return buffer->input_len;
}

void check_input(inputBuffer *buffer) {

  char *command = buffer->tc.argv[0];

  bool rv = is_builtin(buffer);
  if (!rv) {
    char *program_dir = NULL;
    program_dir = is_in_path(command, __func__);

    if (!program_dir)
      return;

    buffer->validation = true;
    execute_from_path(program_dir, buffer);

    free(program_dir);
  }
}

inputBuffer *parse_single_quote(inputBuffer *buffer) {

  char *input = strdup(buffer->input);
  list *head = NULL;

  uint8_t counter = 0;
  for (int i = 0; input[i]; i++)
    counter = (input[i] == '\'') ? counter + 1 : counter;

  if (counter % 2) {
    free(input);
    exit(FAILED);
  } else if (counter == 0) {
    free(input);
    return NULL;
  }

  char *input_except_command = strtok(input, " ");
  if (strchr(input_except_command, '\''))
    exit(FAILED);

  head = create_node(input_except_command, strlen(input_except_command));

  input_except_command =
      &input_except_command[strlen(input_except_command) + 1];

  bool saw = false; // saw: for when we see single quotation
  char token[MAX_BUFFER_SIZE];
  buffer->tc.argn = 1;

  for (int i = 0, j = 0; input_except_command[i]; i++) {

    if (input_except_command[i] == '\'') {

      if (saw) {
        if (input_except_command[i + 1] == '\'') {
          i++;
        } else {
          saw = false;
          token[j] = 0;
          j = 0;
          add_list(head, create_node(token, strlen(token)));
          buffer->tc.argn++;
        }
      } else if (!saw) {
        saw = true;
      }
      continue;
    } else if (saw == false && input_except_command[i] == ' ')
      continue;

    token[j++] = input_except_command[i];

    if (!input_except_command[i + 1] && !saw) {
      token[j] = 0;
      add_list(head, create_node(token, strlen(token)));
      buffer->tc.argn++;
    }
  }

  char **argv = NULL;
  argv = (char **)calloc(
      buffer->tc.argn + 1,
      sizeof(char *)); // this `+ 1` is for the last elemnt of argv in execv
                       // function which it needs to be NULL.
  int i = 0;
  foreach (head) {
    argv[i] = (char *)calloc(strlen((char *)head->data), sizeof(char));
    strcpy(argv[i++], (char *)head->data);
  }
  argv[i] = NULL;
  buffer->tc.argv = argv;

  free(input);
  free_list(head);
  return buffer;
}
