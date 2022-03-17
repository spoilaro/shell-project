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
        head = head->next;
    }
}

int find_linked_length(Arg *head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

Arg *free_args(Arg *head, char *line) {
    Arg *tmp;

    free(line);
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return head;
}