#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include "common.h"
#include "builtin.h"
#include "linked_list.h"

#define MAX_BUFFER_SIZE 128

inputBuffer create_new_input_buffer(void);
uint8_t capture_input(inputBuffer *buffer);
void check_input(inputBuffer *buffer);
inputBuffer *parse_single_quote(inputBuffer *buffer);
void remove_newline(char *input);

#endif
