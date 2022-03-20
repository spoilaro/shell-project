#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "prompt.h"

int main(int argc, char **argv) {
    // TODO: REWRITE
    char *line = NULL;
    Command *cmd = NULL;

    while (true) {
        line = prompt();
        cmd = build_command(cmd, line);

        if (!exec_built_ins(cmd)) {
            exec_command(cmd);
            if (!exec_command(cmd)) {
                printf("Command not found\n");
            }
        }
    }
}