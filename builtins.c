
#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utility.h"

char *builtins[] = {"cd", "exit"};

bool (*b_func[])(Arg *) = {&b_cd, &b_exit};

bool b_cd(Arg *head) {
    char *dest_path;
    dest_path = strdup(head->next->arg_str);

    if (chdir(dest_path) != 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }
    return true;
}

bool b_exit(Arg *head) {
    printf("Exiting\n");
    exit(0);
    return true;
}

int number_of_builtins() { return sizeof(builtins) / sizeof(char *); }

// Idea for function pointers was copied from here:
// https://brennan.io/2015/01/16/write-a-shell-in-c/
bool built_ins(Arg *head) {
    for (int i = 0; i < number_of_builtins(); i++) {
        if (strcmp(head->arg_str, builtins[i]) == 0) {
            return (*b_func[i])(head);
        }
    }

    return false;
}