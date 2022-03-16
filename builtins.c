
#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utility.h"

// A list of built in commands
char *builtins[] = {"cd", "exit", "path"};

// A list of the addresses of the built in command functions
void * (*b_func[])(Arg *, char *paths[]) = {&b_cd, &b_exit, &b_path};

// Utility to get the number of different builtin commands
int number_of_builtins() { return sizeof(builtins) / sizeof(char *); }

// Built in functions have the prefix b_<function name>

// cd
void * b_cd(Arg *head, char *paths[]) {
    char *dest_path;
    dest_path = strdup(head->next->arg_str);

    if (chdir(dest_path) != 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }
    return dest_path;
}

// exit
void * b_exit(Arg *head, char *paths[]) {
    printf("Exiting\n");
    exit(0);
}

// path
void * b_path(Arg *head, char *paths[]) {
    int i = 0;
    int list_len = find_linked_length(head);
    char *args[list_len];

    while (head != NULL) {
        if(i == 0){
            continue;
        }
        args[i] = strdup(head->arg_str);
        head = head->next;
        i++;
    }
    printf("Len is %d \n", i);
    

}

// Idea for function pointers was copied from here:
// https://brennan.io/2015/01/16/write-a-shell-in-c/
void * built_ins(Arg *head, char *paths[]) {
    for (int i = 0; i < number_of_builtins(); i++) {
        if (strcmp(head->arg_str, builtins[i]) == 0) {
            return (*b_func[i])(head, paths);
        }
    }

    return false;
}