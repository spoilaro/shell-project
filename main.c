#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "prompt.h"

typedef struct path {
  char data[64];
} Path;

int main(int argc, char **argv) {
  char *line = NULL;
  Command *cmd = NULL;
  char *path = "/bin/";

  while (true) {

    // wish> prompt -> returns the raw input line
    line = prompt();

    // Initilizes the cmd structure
    cmd = Command__init(cmd);
    Command__build(cmd, line);

    printf("Arg count is %d \n", cmd->arg_count);
  }
}
