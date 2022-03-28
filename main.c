#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "prompt.h"

typedef struct path{
  char data[64];
} Path;

int main(int argc, char **argv) {
  char *line = NULL;
  Command *cmd = NULL;
  char *path = "/bin/";

  while (true) {

    line = prompt();
    cmd = build_command(cmd, line);

    if (!exec_built_ins(cmd, line)) {
      if (!exec_command(cmd, path)) {
        printf("Command not found\n");
      }
    }

    //TODO Free memory
    line = NULL;
    cmd = NULL;
  }
}
