#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include "common.h"
#include "utils.h"
#include "linked_list.h"
#include <dirent.h>
#include <sys/wait.h>

list* init_path(void);
char *is_in_path(char *command);
void execute_from_path(char *program_dir, inputBuffer *command);

#endif
