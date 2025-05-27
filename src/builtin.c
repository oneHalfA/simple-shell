#include "builtin.h"

static const char *builtin_funcs_names[BUILTIN_FUNCS_NUM] = {
    "cd", "pwd", "echo", "exit", "type"};

void (*builtin_funcs[BUILTIN_FUNCS_NUM])(inputBuffer *) = {
    handle_cd, handle_pwd, handle_echo, handle_exit, handle_type};

void handle_cd(inputBuffer *buffer) {
  char *dest_path = NULL;

  if (buffer->tc.argn <= 1 || !strcmp(buffer->tc.argv[1], "~")) {
    dest_path = getenv("HOME");
  } else {
    dest_path = buffer->tc.argv[1];
  }

  if (chdir(dest_path) != 0) {
    fprintf(stderr, "cd: %s: No such file or directory\n", dest_path);
  }
}

void handle_pwd(inputBuffer *buffer) {
  char cwd[PATH_MAX];

  if (getcwd(cwd, PATH_MAX) != NULL)
    printf("%s\n", cwd);
  else {
    LOG("ERROR: %s\n", "Could not init current working directory.");
  }
}

void handle_echo(inputBuffer *buffer) {
  if (buffer->tc.argn <= 1)
    ;
  else {
    for (int i = 1; i < buffer->tc.argn; i++)
      printf("%s ", buffer->tc.argv[i]);
  }
  printf("\n");
}

void handle_exit(inputBuffer *buffer) {
  int exit_code = 0;

  if (buffer->tc.argn == 2) {
    exit_code = atoi( buffer->tc.argv[1]); // TODO Not complete=> error checking over other inputs
  }
  exit(exit_code);
}

bool is_builtin(inputBuffer *buffer) {
  bool builtin = false;
  char *command = NULL;
  command = buffer->tc.argv[0];

  for (int i = 0; i < BUILTIN_FUNCS_NUM; i++) {
    if (!strcmp(command, builtin_funcs_names[i])) {
      buffer->validation = true;
      builtin = true;
      builtin_funcs[i](buffer);
      break;
    }
  }

  return builtin;
}

void handle_type(inputBuffer *buffer) {
  char *command = buffer->tc.argv[1];
  char *found_program_path = NULL;

  if (!command) {
    return;
  }

  for (int i = 0; i < BUILTIN_FUNCS_NUM; i++) {
    if (!strcmp(command, builtin_funcs_names[i])) {
      printf("%s is a shell builtin\n", command);
      return;
    }
  }

  found_program_path = is_in_path(command, __func__);
  if (!found_program_path)
    printf("%s: not found\n", command);
  else
    free(found_program_path);
}
