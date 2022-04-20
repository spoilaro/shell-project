#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "prompt.h"
#include "path.h"


int main(int argc, char **argv) {
  char *line = NULL;
  Command *cmd = NULL;
  Path *path = NULL;

  path = Path__init(path);
 
  while (true) {

    // wish> prompt -> returns the raw input line
    line = prompt();

    // Initilizes the cmd structure
    cmd = Command__init(cmd);
    Command__build(cmd, line);
    Command__execute(cmd, "/bin/");
  }
}
