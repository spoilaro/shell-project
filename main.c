#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "path.h"
#include "command.h"



char *prompt() {
    size_t len = 0;
    char *line = NULL;

    fprintf(stdout, "\n");
    fprintf(stdout, "wish> ");
    getline(&line, &len, stdin);

    if (strcmp(line, "\n") == 0) {
        return NULL;
    } else {
        printf("\n");
        line[strcspn(line, "\n")] = 0;

        return line;
    }
}

int main(int argc, char **argv) {
  char *line = NULL;
  Command *cmd = NULL;
  Path *path = NULL;

  // Built in function names
  char *func_names[] = {"exit"};
  int num_func_names = sizeof(func_names) / sizeof(char  *);


  path = Path__init(path);
 
  while (true) {

    // wish> prompt -> returns the raw input line
    line = prompt();

    // Initilizes the cmd structure
    cmd = Command__init(cmd);
    Command__build(cmd, line);
    Command__execute(cmd, "/bin/");

    //TODO Built ins

  }
}

