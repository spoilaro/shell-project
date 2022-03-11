#define _GNU_SOURCE
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
    int list_len = find_linked_length(arg_head);
    int i = 0;
    pid_t pid;
    char *args[list_len - 1];
    char *command = arg_head->arg_str;

    printf("Arg len %d\n", list_len);

    while (arg_head != NULL) {
        int cmp_res = strcmp(command, arg_head->arg_str);

        if (cmp_res == 0) {
            arg_head = arg_head->next;
            continue;
        }
        args[i] = arg_head->arg_str;
        arg_head = arg_head->next;
        i++;
    }

    args[list_len - 1] = NULL;

    // for (int j; j < list_len; j++) {
    // printf("li %s\n", args[j]);
    //}

    char *test_args[] = {"-l", NULL};

    int rc = fork();
    if ((pid = fork()) == -1) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    } else if (pid == 0) {
        execv("/bin/ls", args);
    } else {
        int rc_wait = wait(NULL);
        printf("Parent here\n");
    }
}

// TODO: Builtins