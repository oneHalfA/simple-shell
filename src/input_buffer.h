#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include "common.h"
#include "builtin.h"
#include "linked_list.h"
#include "parse_symbol.h"


inputBuffer create_new_input_buffer(void);
uint8_t capture_input(inputBuffer *buffer);
void check_input(inputBuffer *buffer);
void remove_newline(char *input);

#endif
