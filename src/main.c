#include "input_buffer.h"

list *path = NULL;
int main(void) {

  setbuf(stdout, NULL);
  path = init_path();


  inputBuffer buffer = create_new_input_buffer();
  printf("$ ");
  while (capture_input(&buffer)) {

    check_input(&buffer);

    if (buffer.validation == false)
      printf("%s: command not found\n", buffer.input);

    printf("$ ");

    free_buffer(&(buffer.tc));
  }

  free(buffer.input);
  free_list(path);

  return OK;
}
