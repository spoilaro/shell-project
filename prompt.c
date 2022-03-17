#define _GNU_SOURCE
#include "prompt.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *prompt() {
    size_t len = 0;
    char *line;

    fprintf(stdout, "wish> ");
    getline(&line, &len, stdin);

    if (strcmp(line, "\n") == 0) {
        return NULL;
    } else {
        printf("\n");
        line[strcspn(line, "\n")] = 0;

        return line;
    }
}

Command *build_command(Command *cmd, char *line) {
    char *delim = " ";
    char *buff = line;
    char *parsed_arg;
    int index = 0;
    char *args[MAX_ARG_COUNT];
    int redirect = 0;

    cmd = (Command *)malloc(sizeof(Command));

    while ((parsed_arg = strtok_r(buff, delim, &buff))) {
        if (index == 0) {
            cmd->command = strdup(parsed_arg);
            args[index] = parsed_arg;
        } else {
            args[index] = parsed_arg;
            if (strcmp(parsed_arg, ">") == 0) {
                redirect = index;
            } else if (strcmp(parsed_arg, "<") == 0) {
                redirect = -1 * index;
            }
        }

        index++;
    }
    if (redirect > 0) {
        cmd->out_file = strdup(args[redirect + 1]);
    } else if (redirect < 0) {
        cmd->in_file = strdup(args[abs(redirect) + 1]);
    }

    args[index] = NULL;

    cmd->args = args;

    return cmd;
}

void exec_command(Command *cmd) {
    char dest_path[MAX_PATH_LEN];

    int rc = fork();
    if (rc < 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    } else if (rc == 0) {
        char *path = "/bin/";
        strcat(dest_path, path);
        strcat(dest_path, cmd->command);
        execv(dest_path, cmd->args);
    } else {
        int rc = wait(NULL);
    }
}