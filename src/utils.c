#include "utils.h"

void print_log(const char *f, ...) {
  va_list args;
  va_start(args, f);
  printf("\033[1;36m");
  vprintf(f, args);
  printf("\033[0m\n");
  va_end(args);
}

void free_buffer(tokenizedFormat *t) {
  for (int i = 0; i < t->argn; i++) {
    free(t->argv[i]);
    t->argv[i] = NULL;
  }
  free(t->argv);
  t->argv = NULL;
}
