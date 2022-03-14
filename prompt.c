#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utility.h"

char *prompt(char *line) {
    size_t len = 0;

    fprintf(stdout, "wish> ");
    getline(&line, &len, stdin);

    printf("\n");

    line[strcspn(line, "\n")] = 0;

    return line;
}

Arg *parse_line(char *line, Arg *head) {
    char *delim = " ";
    char *buf = line;
    char *parsed_arg;

    while ((parsed_arg = strtok_r(buf, delim, &buf))) {
        head = new_argument(head, parsed_arg);
    }

    return head;
}

void exec_path_commands(Arg *arg_head) {
    int list_len = find_linked_length(arg_head) + 1;
    int i = 0;
    pid_t pid;
    char *args[list_len];

    while (arg_head != NULL) {
        args[i] = strdup(arg_head->arg_str);
        arg_head = arg_head->next;
        i++;
    }

    args[list_len - 1] = NULL;

    if ((pid = fork()) == -1) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    } else if (pid == 0) {
        // Path to executable
        char path[100] = "/bin/";
        char path_sec[100] = "/usr/bin/";
        strcat(path, args[0]);
        if (execv(path, args)) {
            strcat(path_sec, args[0]);
            execv(path_sec, args);
            // TODO: "/usr/bin" path and error handling
        }
    } else {
        wait(NULL);
    }
}

// TODO: redirecting