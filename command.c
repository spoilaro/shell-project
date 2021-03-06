#include "command.h"
#define _GNU_SOURCE

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

Command *Command__init(Command *self) {
  self = (Command *)malloc(sizeof(Command));

  if (self == NULL) {
    // TODO Error
  }
  self->command = "";
  self->arg_count = 0;
  self->in_file = NULL;
  self->out_file = NULL;
  self->args = NULL;

  return self;
}

void Command__free(Command *cmd) {
  // TODO Free
}


void Command__build(Command *self, char *line) {
  // Builds the actual command from the raw input line
  // char *args[0] will be the command itself
  // char *args[n+1] will be an argument
  //
  // TODO Redirecting

  char *parsed_arg = NULL;
  int index = 0;

  self->args = malloc(10 * sizeof(char *));

  while ((parsed_arg = strtok_r(line, " ", &line))) {

    if (index == 0) {
      self->command = strdup(parsed_arg);
    }

    self->args[index] = strdup(parsed_arg);
    index++;
  }
  // Account for the command in the array
  self->arg_count = index - 1;
}

// Executes not built in commands like "ls"
void Command__execute(Command *self, char *path) {
  char dest_path[100] ="";

  // Creates path like "/bin/ls/"
  strcat(dest_path, path); 
  strcat(dest_path, self->command);

  int rc = fork();
  if (rc < 0) {
    write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));

  } else if (rc == 0) {

    if (execv(dest_path, self->args)) {
      write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }

  } else {
    int rc = wait(NULL);
  }
}

