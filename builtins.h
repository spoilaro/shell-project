#ifndef _BUILTINSH_
#define _BUILTINSH_

#include <stdbool.h>

#include "prompt.h"

bool b_exit(Command *);

bool exec_built_ins(Command *cmd);

int built_in_count();

#endif