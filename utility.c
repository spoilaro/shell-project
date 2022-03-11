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

int find_linked_length(Arg *head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

// char *convert_to_array(int len, Arg *head, char *args) {
// int i = 0;
// char *buff_args[len];

// while (head != NULL) {
// buff_args[i] = head->arg_str;
// i++;
// head = head->next;
//}
// args = buff_args;
// return buff_args;
//}