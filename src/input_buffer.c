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

  int rv = parse_quote(buffer);
  if (rv) {
    return 0;
  }

  return buffer->input_len;
}

void check_input(inputBuffer *buffer) {

  char *command = buffer->tc.argv[0];

  bool rv = is_builtin(buffer);
  if (!rv) {
    char *program_dir = NULL;
    program_dir = is_in_path(command);

    if (!program_dir)
      return;

    buffer->validation = true;
    execute_from_path(program_dir, buffer);

    free(program_dir);
  }
}
