#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include "common.h"
#include "utils.h"
#include "linked_list.h"
#include "parse_symbol.h"
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>


#define DEFAULT_MODE 0644
#define OPEN_APPEND (O_WRONLY | O_CREAT | O_APPEND), DEFAULT_MODE
#define OPEN_OVERWRITE (O_WRONLY | O_CREAT | O_TRUNC), DEFAULT_MODE

#define open_file(path, TYPE) \
        open(path, TYPE)

#define assert(cond, method, msg)     \
        do {                          \
          if (cond) {                 \
            LOG("%s",msg);            \
            method;                   \
            exit(EXIT_FAILURE);       \
          }                           \
        } while (0)

list* init_path(void);
char *is_in_path(char *command);
void execute_from_path(char *program_dir, inputBuffer *command);
void do_redirections(inputBuffer* buf);

#endif
