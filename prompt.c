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
    char *buf = line;
    char *parsed_arg;

    while ((parsed_arg = strtok_r(buf, delim, &buf))) {
        head = new_argument(head, parsed_arg);
    }

    return head;
}

// TODO: Builtins