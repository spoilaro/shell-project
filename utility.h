#define ERRMSG "An error has occurred\n"
#define MAX_ARG_LEN 100

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
