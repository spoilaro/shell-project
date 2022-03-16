#include <stdbool.h>

#define ERRMSG "An error has occurred\n"
#define MAX_ARG_LEN 100
#define MAX_PATH_LEN 256

typedef struct Arg {
    char *arg_str;
    struct Arg *next;
} Arg;

char *prompt(char *line);

Arg *parse_line(char *line, Arg *head);

Arg *new_argument(Arg *head, char *arg_str);

void show_args(Arg *head);

void exec_path_commands(Arg *arg_head);

int find_linked_length(Arg *head);

char *convert_to_array(int len, Arg *head, char *args);

Arg *free_args(Arg *head);

void * built_ins(Arg *head, char *paths[]);

int number_of_builtins();

void * b_cd(Arg *head, char *paths[]);

void * b_exit(Arg *head, char *paths[]);

void * b_path(Arg *head, char *paths[]);
