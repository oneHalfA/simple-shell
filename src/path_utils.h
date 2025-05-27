#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include "common.h"
#include "utils.h"
#include <dirent.h>
#include <sys/wait.h>

void tokenize_path(tokenizedFormat *paths, const char *path_env);
char *is_in_path(char *command, const char *caller);
void execute_from_path(char *program_dir, inputBuffer *command);

#endif
