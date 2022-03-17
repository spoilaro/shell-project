#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

int main(int argc, char **argv) {
    char *line = NULL;
    Arg *arg_head = NULL;
    bool built_in = false;

    // Paths
    char *paths[MAX_NUM_OF_PATHS] = {"/usr/bin/"};

    switch (argc) {
        // Interactive mode
        case 1:
            while (true) {
                line = prompt(line);
                arg_head = parse_line(line, arg_head);

                // Handling the path change
                if (strcmp(arg_head->arg_str, "path") == 0) {
                    // TODO: Change path
                    change_path(arg_head, paths);
                    continue;
                }

                built_in = built_ins(arg_head);
                if (!built_in) {
                    exec_path_commands(arg_head, paths);
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