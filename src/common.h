#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h> // chdir is here
#include <string.h>
#include <stdlib.h> // getenv is here

#define OK 0
#define FAILED 1
#define MAX_BUFFER_SIZE 128

typedef struct {
  char **argv;
  uint8_t argn;
} tokenizedFormat;

typedef struct {
  char *input;
  uint8_t input_len;
  bool validation;
  tokenizedFormat tc;
  uint8_t redirection_flag;
} inputBuffer;

typedef struct list {
  struct list *next;
  void *data;
} list;

extern list *path;

#endif
