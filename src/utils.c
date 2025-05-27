#include "utils.h"

void print_log(const char *f, ...) {
  va_list args;
  va_start(args, f);
  printf("\033[1;36m");
  vprintf(f, args);
  printf("\033[0m\n");
  va_end(args);
}

void free_buffer(tokenizedFormat *t, char type) {
  uint8_t len = 0;
  switch (type) {
  case 'p': // for path
    len = t->argn;
    break;
  case 'b': // for buffer
    len = t->argn + 1;  // +1 because execv function needs to have null terminated argv
    break;
  default:
    LOG("WRONG TYPE `%c` TO FREE MEMORY", type);
    exit(1);
    break;
  }

  for (int i = 0; i < len; i++) {
    free(t->argv[i]);
    t->argv[i] = NULL;
  }
  free(t->argv);
  t->argv = NULL;
}
