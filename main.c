#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prompt.h"

int main(int argc, char **argv) {
    // TODO: REWRITE
    char *line = NULL;
    Command *cmd = NULL;
    bool run_built_in = true;

    while (true) {
        line = prompt();
        cmd = build_command(cmd, line);
        run_built_in = exec_command(cmd);
        if (!run_built_in) {
            printf("Running built in \n");
        }
    }
}