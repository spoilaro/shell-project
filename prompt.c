#define _GNU_SOURCE
#include "prompt.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


Command *init_command(Command *cmd){
  
  cmd = malloc(sizeof(Command));
  if (cmd == NULL){
    // TODO Error
  }

  return cmd;
}

char *prompt() {
    size_t len = 0;
    char *line = NULL;

    fprintf(stdout, "\n");
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


bool exec_command(Command *cmd, char *path) {
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
        strcat(dest_path, path);
        strcat(dest_path, cmd->command);

        // If output stream, redirect
        if (out) {
            dup2(out, 1);
        }
        
        printf("Path is %s\n", dest_path);
        if (execv(dest_path, cmd->args)) {
            // TODO: Redirect stderror too
            success = false;
        }

    } else {
        int rc = wait(NULL);
    }
    return success;
}

void free_cmd(Command *cmd) {
    free(cmd->command);
    cmd->command = NULL;

    free(cmd->out_file);
    free(cmd->in_file);

    cmd->out_file = NULL;
    cmd->in_file = NULL;

    // for (int i = 0; i < cmd->arg_count; i++) {
    // free(cmd->args[i]);
    //}
    free(cmd);
    cmd = NULL;
}
