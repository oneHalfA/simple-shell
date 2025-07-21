#include "path_utils.h"

list* init_path(void) {
  list* path = NULL;
  char *path_var = getenv("PATH");

  if (!path_var) {
    LOG("Could not initialize path variable: env_path = %p", path_var);
    exit(FAILED);
  }

  char env_path[strlen(path_var) + 1];
  strcpy(env_path, path_var);


  char *token = strtok(env_path, ":");
  if (!token) {
    LOG("PATH does not have value: token = %p", token);
    exit(FAILED);
  }

  path = create_node(token, strlen(token));
  while ((token = strtok(NULL, ":"))) {
    add_list(path, create_node(token, strlen(token)));
  }
  return path;
}

void execute_from_path(char *program_dir, inputBuffer *buf) {

  char *absoulte_path = NULL;
  char *commandName = NULL;
  commandName = buf->tc.argv[0];

  uint8_t len = strlen(program_dir);
  len += strlen(commandName);

  absoulte_path = (char *)calloc(1, len + 2); // +2 = 1 ('\0') + 1 ('\')

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

char *is_in_path(char *command) {

  DIR *dir_stream = NULL;
  struct dirent *entry = NULL;

  char *found = NULL;
  char *dir = NULL;
  list* path_copy = path;

  foreach (path_copy) {

    dir = path_copy->data;
    dir_stream = opendir(dir);

    if (!dir_stream)
      continue;

    while ((entry = readdir(dir_stream)) != NULL)
      if (!strcmp(entry->d_name, command)) {
        found = strdup(dir);
        closedir(dir_stream);
        return found;
      }
    closedir(dir_stream);
  }
  return NULL;
}
