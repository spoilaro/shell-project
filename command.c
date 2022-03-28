#include "command.h"
#include <stdio.h>
#include <stdlib.h>

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
  self->command = "Hello World\n";
  self->arg_count = 0;
  self->in_file = NULL;
  self->out_file = NULL;
  self->args = NULL;

  return self;
}

void Command__free(Command *cmd) {
  // TODO Free
}

char *Command__cmd(Command *self) { return self->command; }

// Get the argument with index
char *Command__arg(Command *self, int i) { return self->args[i]; }

// Get redirect output file
char *Command__outfile(Command *self) { return self->out_file; }

// Get redirect input file
char *Command__infile(Command *self) { return self->in_file; }

int Command__arg_count(Command *self) { return self->arg_count; }

void Command__build(Command *self, char *line) {
  // Builds the actual command from the raw input line
  // char *args[0] will be the command itself
  // char *args[n+1] will be an argument
  //
  // TODO Redirecting

  char *parsed_arg = NULL;
  int index = 0;
  char *args[10];

  while ((parsed_arg = strtok_r(line, " ", &line))) {

    if (index == 0) {
      self->command = strdup(parsed_arg);
      args[index] = parsed_arg;
    }

    args[index] = parsed_arg;
    index++;
  }

  args[index] = NULL;

  self->args = args;

  // Account for the command in the array
  self->arg_count = index - 1;
}
