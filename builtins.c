
#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utility.h"

// A list of built in commands
char *builtins[] = {"cd", "exit"};

// A list of the addresses of the built in command functions
bool (*b_func[])(Arg *) = {&b_cd, &b_exit};

// Utility to get the number of different builtin commands
int number_of_builtins() { return sizeof(builtins) / sizeof(char *); }

// Built in functions have the prefix b_<function name>

// cd
bool b_cd(Arg *head) {
    char *dest_path;
    dest_path = strdup(head->next->arg_str);

    printf("Dest path is %s \n", dest_path);

    if (chdir(dest_path) != 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }
    return true;
}

// exit
bool b_exit(Arg *head) {
    printf("Exiting\n");
    exit(0);
}

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
