#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

char *prompt(char *line) {
    size_t len = 0;

    fprintf(stdout, "wish> ");
    getline(&line, &len, stdin);

    printf("\n");
    return line;
}

// TODO: Parse to commands
Arg *parse_line(char *line, Arg *head) {
    char *delim = " ";
    char *parsed_arg = strtok(line, delim);

    while (parsed_arg != NULL) {
        head = new_argument(head, parsed_arg);
        parsed_arg = strtok(NULL, delim);
    }
    return head;
}

// TODO: Builtins