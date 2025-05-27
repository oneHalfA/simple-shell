#ifndef BUILTIN_H
#define BUILTIN_H

#include "common.h"
#include "utils.h"
#include <limits.h>
#include "path_utils.h"

#define BUILTIN_FUNCS_NUM 5


void handle_cd(inputBuffer *buffer);
void handle_echo(inputBuffer *buffer);
void handle_pwd(inputBuffer *buffer);
void handle_exit(inputBuffer *buffer);
void handle_type(inputBuffer *buffer);
bool is_builtin(inputBuffer *buffer);

#endif
