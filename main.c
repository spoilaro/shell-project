#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "path.h"
#include "command.h"


// Prompt wish>
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

// Built in function for cd
void b_cd(char *dest){
  if (chdir(dest) != 0) {
        write(STDERR_FILENO, ERRMSG, strlen(ERRMSG));
    }
}

// Built in function for exit
void b_exit(char *dest){
  exit(0);
}

// Checks if there is built in command and executes it if found
bool run_built_in(Command *cmd){

  // List of function names
  char *func_names[] = {"exit", "cd"};

  // Number of built in commands
  int num_func_names = sizeof(func_names) / sizeof(char  *);

  // Function pointes to built in command functions
  void (*func_p[])(char *) = {&b_cd, &b_exit};

    // Checks if there is built in command and runs it
    for (int i=0; i<num_func_names; i++){
      if (strcmp(cmd->command, func_names[i]) == 0){
        (*func_p)(cmd->args[1]);
        return true;
      }
    }
    // Returns false if there was no built in command
    return false;
}

int main(int argc, char **argv) {
  char *line = NULL;
  Command *cmd = NULL;
  Path *path = NULL;

  // Built in function names

  path = Path__init(path);
 
  while (true) {

    //(*func_p[0])("C");

    // wish> prompt -> returns the raw input line
    line = prompt();

    // Initilizes the cmd structure
    cmd = Command__init(cmd);
    Command__build(cmd, line);

    if (run_built_in(cmd)) {
      continue;
    }

    // Executes a program from given path
    // TODO Use Path object
    Command__execute(cmd, "/bin/");
  }
}

