#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

int main(int argc, char **argv) {
    char *line;
    Arg *arg_head = NULL;
    bool built_in = false;

    switch (argc) {
        // Interactive mode
        case 1:
            while (true) {
                line = prompt(line);
                arg_head = parse_line(line, arg_head);

                built_in = built_ins(arg_head);
                if (!built_in) {
                    exec_path_commands(arg_head);
                }

                arg_head = free_args(arg_head);
            }

            break;

        // Batch mode
        case 2:
            break;

        default:
            break;
    }

    return 0;
}