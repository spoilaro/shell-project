#include "builtins.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "prompt.h"

char *built_ins[] = {"exit", "cd"};
bool (*b_func_p[])(Command *cmd) = {&b_exit, &b_cd};

bool b_exit(Command *cmd) {
    printf("Exiting\n");
    exit(0);
}

bool b_cd(Command *cmd) {
    char *dest_path = cmd->args[1];

    if (chdir(dest_path) != 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }

    return true;
}

int built_in_count() { return sizeof(built_ins) / sizeof(char *); }

bool exec_built_ins(Command *cmd) {
    for (int i = 0; i < built_in_count(); i++) {
        // TODO: Execute right function
        if (strcmp(built_ins[i], cmd->command) == 0) {
            return (b_func_p[i])(cmd);
        }
    }
    return false;
}
