#ifndef _PROMPTH_
#define _PROMPTH_

#define MAX_ARG_COUNT 10
#define ERRMSG "An error has occurred\n"
#define MAX_PATH_LEN 256

#include <stdbool.h>

typedef struct Command {
    int arg_count;
    char *command;
    char **args;
    char *out_file;
    char *in_file;
} Command;

char *prompt(void);

Command *build_command(Command *, char *);

bool exec_command(Command *, char *);

void free_cmd(Command *);

#endif