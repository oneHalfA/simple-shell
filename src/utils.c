#include "utils.h"
#include <stdarg.h>

void print_log(const char *f, ...) {
  va_list args;
  va_start(args, f);
  printf("\033[1;36m");
  vprintf(f, args);
  printf("\033[0m\n");
  va_end(args);
}
