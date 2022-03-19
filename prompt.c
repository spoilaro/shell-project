#define _GNU_SOURCE
#include "prompt.h"

#include <fcntl.h>
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

            // Setting redirect filenames

        } else {
            // If ">" or "<" then next token is either output or input filename
            if (strcmp(parsed_arg, ">") == 0) {
                redirect = 1;
                continue;
            } else if (strcmp(parsed_arg, "<") == 0) {
                redirect = -1;
                continue;
            } else if (redirect == 1) {
                cmd->out_file = strdup(parsed_arg);
                continue;
            } else {
                args[index] = parsed_arg;
            }

            // continue;
        }

        index++;
    }
    args[index] = NULL;

    cmd->args = args;

    return cmd;
}

bool exec_command(Command *cmd) {
    char dest_path[MAX_PATH_LEN];
    bool success = true;
    int out = 0;

    // Opening output stream if output filename was given
    if (cmd->out_file != NULL) {
        // https://stackoverflow.com/questions/28466715/using-open-to-create-a-file-in-c
        if ((out = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) ==
            -1) {
            write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
        }
    }

    int rc = fork();
    if (rc < 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    } else if (rc == 0) {
        char *path = "/bin/";
        strcat(dest_path, path);
        strcat(dest_path, cmd->command);

        // If output stream, redirect
        if (out) {
            dup2(out, 1);
        }
        //
        if (execv(dest_path, cmd->args)) {
            // TODO: Redirect stderror too
            success = false;
        }
    } else {
        int rc = wait(NULL);
    }
    return success;
}
