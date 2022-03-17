typedef struct SimpleCommand {
    int _available_arg_count;
    int _arg_count;
    char **_args;
    SimpleCommand();
    void insertArgument(char *argument);
} SimpleCommand;

typedef struct Command {
    int _available_scommand_count;
    int _scommand_count;
    SimpleCommand **_simple_commands;
    char *_outfile;
    char *_inputfile;
    char *_errfile;
    int _background;

    void prompt();
    void print();
    void execute();
    void clear();

    Command();
    void insert_s_command(SimpleCommand *s_command);

    static Command _current_command;
    static SimpleCommand *_current_simple_command;
} Command;
