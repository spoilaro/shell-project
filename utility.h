#define ERRMSG "An error has occurred\n"

typedef struct Arg {
    char *arg_str;
    struct Arg *next;
} Arg;

char *prompt(char *line);
Arg *parse_line(char *line, Arg *head);
Arg *new_argument(Arg *head, char *arg_str);
void show_args(Arg *head);