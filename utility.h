#include <stdbool.h>

#define ERRMSG "An error has occurred\n"
#define MAX_ARG_LEN 100
#define MAX_PATH_LEN 256
#define MAX_NUM_OF_PATHS 100

typedef struct Arg {
    char *arg_str;
    struct Arg *next;
} Arg;

char *prompt(char *line);

Arg *parse_line(char *line, Arg *head);

Arg *new_argument(Arg *head, char *arg_str);

void show_args(Arg *head);

void exec_path_commands(Arg *arg_head, char *paths[]);

int find_linked_length(Arg *head);

char *convert_to_array(int len, Arg *head, char *args);

Arg *free_args(Arg *head);

bool built_ins(Arg *head);

int number_of_builtins();

bool b_cd(Arg *head);

bool b_exit(Arg *head);

void change_path(Arg *head, char *paths[]);