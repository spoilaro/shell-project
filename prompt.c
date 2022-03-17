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

    // if (strcasecmp(line, "\n") == 0) {
    // return NULL;
    //}

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

void exec_path_commands(Arg *arg_head, char *path) {
    int list_len = find_linked_length(arg_head) + 1;
    int i = 0;
    pid_t pid;
    char *args[list_len];
    char dest[MAX_PATH_LEN];

    // Converts a linked list to a regular array
    while (arg_head != NULL) {
        args[i] = strdup(arg_head->arg_str);
        arg_head = arg_head->next;
        i++;
    }
    args[list_len - 1] = NULL;

    // Starts a new process

    // If fork returns -1, the new process was not able to be created
    if ((pid = fork()) == -1) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    } else if (pid == 0) {
        // fork() returns 0 => new child process was created
        strcat(dest, path);
        strcat(dest, args[0]);

        if (access(dest, F_OK) == 0) {
            printf("OK\n");
        }

        // TODO: Error handling when nothing executes
    } else {
        // Parent process waits for the child process to catch up
        int rc = wait(NULL);
    }
}

// TODO: redirecting