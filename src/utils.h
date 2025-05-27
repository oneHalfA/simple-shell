#ifndef UTILS_H
#define UTILS_H

#include "common.h"
#include <stdarg.h>


#define LOG(format, ...)                                                       \
  printf("\033[1;31m");                                                        \
  printf("( %s : %d ) ", __func__, __LINE__);                                  \
  printf("\033[0m");                                                           \
  print_log(format, __VA_ARGS__)

void print_log(const char *format, ...);
void free_buffer(tokenizedFormat *t, char type);

#endif
