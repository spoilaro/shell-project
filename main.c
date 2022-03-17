#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prompt.h"

int main(int argc, char **argv) {
    // TODO: REWRITE
    char *line = NULL;
    Command *cmd;

    while (true) {
        line = prompt();
        cmd = build_command(cmd, line);
        exec_command(cmd);
    }

    return 0;
}