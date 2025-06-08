#ifndef PARSE_SYMBOL_H
#define PARSE_SYMBOL_H

#include "common.h"

#define SQ '\''
#define DQ '"'
#define BACK_SLASH '\\'

#define IS_VALID_BACKSLASH(str, index) \
        (str[index] == BACK_SLASH && str[index + 1] != '\0')

struct str_quote_s{
  char str_between[MAX_BUFFER_SIZE];
  int inx;
  bool finished;
};

typedef struct str_quote_s str_quote_t;

int parse_quote(inputBuffer *buffer);
void reset(str_quote_t *tmp);
void skip_delim(char *str, int *index);

#endif
