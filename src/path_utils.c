#include "path_utils.h"


void tokenize_path(tokenizedFormat *paths, const char *path_env) {
  char *path_env_copy = strdup(path_env);
  char *token = strtok(path_env_copy, ":");
  paths->argn = 0;

  if (token == NULL) {
    fprintf(stderr, "Error: No path in PATH variable.\n");
    exit(EXIT_FAILURE);
  }

  while (token) {
    paths->argn++;
    token = strtok(NULL, ":");
  }

  strcpy(path_env_copy, path_env);

  paths->argv = (char **)calloc(paths->argn, sizeof(char *));

  token = strtok(path_env_copy, ":");
  for (int i = 0; i < paths->argn; ++i) {
    paths->argv[i] = (char *)calloc(1, strlen(token) + 1);
    token = strtok(NULL, ":");
  }

  free(path_env_copy);
}

void execute_from_path(char *program_dir, inputBuffer *buf) {

  char *absoulte_path = NULL;
  char *commandName = NULL;
  commandName = buf->tc.argv[0];

  uint8_t len = strlen(program_dir);
  len += strlen(commandName);

  absoulte_path = (char *)calloc(1, len + 2); // +2  = 1 ('\0') + 1 ('\')

  strcpy(absoulte_path, program_dir);
  strcat(absoulte_path, "/");
  strcat(absoulte_path, commandName);

  pid_t pid = fork();
  if (pid == 0) {
    execv(absoulte_path, buf->tc.argv);
    printf("%s %s %s \n", buf->tc.argv[0], buf->tc.argv[1], buf->tc.argv[2]);

    LOG("Could not execute %s child process properly.\n", buf->tc.argv);
  } else if (pid > 0)
    wait(NULL);

  free(absoulte_path);
}

char *is_in_path(char *command, const char *func_caller) {

  DIR *dir_stream = NULL;
  struct dirent *entry = NULL;

  char *found = NULL;

  char *path_copy = strdup(path);
  char *dir = strtok(path_copy, ":");

  while (dir != NULL) {
    dir_stream = opendir(dir);

    if (!dir_stream) {
      dir = strtok(NULL, ":");
      continue;
    }

    while ((entry = readdir(dir_stream)) != NULL) {
      if (!strcmp(entry->d_name, command)) {
        if (!strcmp(func_caller, "handle_type"))
          printf("%s is %s/%s\n", command, dir, command);
        found = strdup(dir);
        goto here;
      }
    }
    dir = strtok(NULL, ":");
  }
here:
  free(path_copy);
  closedir(dir_stream);
  return found;
}
