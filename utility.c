#include "utility.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Arg *new_argument(Arg *head, char *arg_str) {
    Arg *tmp;

    Arg *new = (Arg *)malloc(sizeof(Arg));
    if (new == NULL) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }
    new->arg_str = arg_str;
    new->next = NULL;

    if (head == NULL) {
        return new;
    }

    tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;

    return head;
}

void show_args(Arg *head) {
    while (head != NULL) {
        printf("Arg is %s\n", head->arg_str);
        head = head->next;
    }
}