#include <stdbool.h>
#include <stdio.h>

#include "utility.h"

int main(int argc, char **argv) {
    char *line;
    Arg *arg_head = NULL;

    switch (argc) {
        // Interactive mode
        case 1:
            while (true) {
                line = prompt(line);
                arg_head = parse_line(line, arg_head);
            }

            // TODO: Free line before exiting
            break;

        // Batch mode
        case 2:
            break;

        default:
            break;
    }

    return 0;
}