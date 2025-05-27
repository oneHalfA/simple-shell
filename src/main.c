#include "path_utils.h"
#include "input_buffer.h"

const char* path = NULL;
int main(void) {

  setbuf(stdout, NULL);
  path = getenv("PATH");
  tokenizedFormat paths;
  tokenize_path(&paths, path);

  inputBuffer buffer = create_new_input_buffer();
  printf("$ ");
  while (capture_input(&buffer)) {

    check_input(&buffer);

    if (buffer.validation == false)
      printf("%s: command not found\n", buffer.input);

    printf("$ ");

    free_buffer(&(buffer.tc), 'b');
  }

  free_buffer(&paths, 'p');
  free(buffer.input);

  return OK;
}
