#include "parse_symbol.h"
#include "linked_list.h"

void reset(str_quote_t *tmp) {
  tmp->finished = false;
  tmp->inx = 0;
  memset(tmp, 0, 128);
}

void skip_delim(char *str, int *index) {
  for (; str[*index + 1] == '\t' || str[*index + 1] == ' '; (*index)++)
    ;
}

int parse_quote(inputBuffer *buffer) {

  char *input = buffer->input;
  list *head = NULL;

  char token[MAX_BUFFER_SIZE]; // token is the final form of argument that will be added to the list.

  bool saw_d = false;
  bool saw_s = false;
  str_quote_t str;
  int index = 0;

  reset(&str);
  
  for (int i = 0; input[i]; i++) {

        // ================================================== set the str if saw SQ
        if (input[i] == SQ && saw_d == false) {
            saw_s = !saw_s;
            if (input[i + 1] != SQ)
                str.finished = !saw_s;
        } else if (input[i] == DQ && saw_s == false) {
            saw_d = !saw_d;
            if (input[i + 1] != DQ)
                str.finished = !saw_d;
        }
        // ================================================== fill str or concatenate it with token
        if ((saw_s && input[i] != SQ)) {
            str.str_between[str.inx++] = input[i];
        } else if (saw_d && input[i] != DQ) {
            if (IS_VALID_BACKSLASH(input, i) &&
                (input[i + 1] == BACK_SLASH || input[i + 1] == '"' || input[i + 1] == '$' ||
                 input[i + 1] == '`')) { // Parse BACK_SLASH within double quotes
                str.str_between[str.inx++] = input[++i];
            } else
                str.str_between[str.inx++] = input[i];
        } else if (str.finished) {
            str.str_between[str.inx] = 0;
            token[index] = 0;
            strcat(token, str.str_between);
            index += str.inx;
            reset(&str);
        }
        // ================================================== add token to the list
        if (!saw_d && !saw_s && str.finished == false) {
            if (input[i] == '\t' || input[i] == ' ') {

                skip_delim(input, &i);
                token[index] = 0;
                head = add_list(head, create_node(token, strlen(token)));
                buffer->tc.argn++;
                index = 0;
            } else {
                if (input[i] != SQ && input[i] != DQ) {
                    if (IS_VALID_BACKSLASH(input, i)) // If SAW UNQUOTED back_slash
                        token[index++] = input[++i];
                    else
                        token[index++] = input[i];
                }
                if (!input[i + 1]) {
                    token[index] = 0;
                    head = add_list(head, create_node(token, strlen(token)));
                    buffer->tc.argn++;
                    index = 0;
                }
            }
        }
    }

  if (saw_d || saw_s) {
    return FAILED;
  }

  char **argv = NULL;
  argv = (char **)calloc(
      buffer->tc.argn + 1,
      sizeof(char *)); // The `+ 1` is for the last element of argv in execv
                       // function which it needs to be NULL.

  int i = 0;
  foreach (head) {
    argv[i] = (char *)calloc(strlen((char *)head->data), sizeof(char));
    strcpy(argv[i++], (char *)head->data);
  }
  argv[i] = NULL;
  buffer->tc.argv = argv;

  free_list(head);

  return OK;
}


void check_redirection(inputBuffer *buffer){
    char** argv = buffer->tc.argv;
    uint8_t argn  = buffer->tc.argn;

    if (argn >= 3){
        if (strchr(argv[argn - 2],'>')){
            if (!strcmp(argv[argn - 2], ">>")) {
                // APPEND REDIRECTION
            }
            else if(argv[argn - 2][1] == '\0' || argv[argn - 2][0] == '1'){
                // OUTPUT REDIRECTION
                buffer->redirection_flag = r_out;
            }
            else if(argv[argn - 2][0] == '2'){
                // ERR REDIRECTION
                buffer->redirection_flag = r_err;
            }
        }
        argv[argn - 2] = NULL;
    }
}
