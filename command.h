

typedef struct Command {
    int arg_count;
    char *command;
    char **args;
    char *out_file;
    char *in_file;
} Command;


// Initialize the command
Command *Command__init(Command *);

// Destructuring of the command
void Command__free(Command *);

// Get the current command, for example "ls" or "wc"
char *Command__cmd(Command *self);

// Get the argument with index
char *Command__arg(Command *self, int);

char *Command__outfile(Command *self);

char *Command__infile(Command *self);

int Command__arg_count(Command *self);

void Command__build(Command *self, char *line);

void Command__execute(Command *self, char *path);

