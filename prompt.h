#define MAX_ARG_COUNT 10
#define ERRMSG "An error has occurred\n"
#define MAX_PATH_LEN 256

typedef struct Command {
    int arg_count;
    char *command;
    char **args;
    char *out_file;
    char *in_file;
} Command;

char *prompt(void);
Command *build_command(Command *, char *);
void exec_command(Command *);