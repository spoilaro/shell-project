#ifndef _BUILTINSH_
#define _BUILTINSH_

#include <stdbool.h>

#include "prompt.h"

bool b_exit(Command *);
bool b_cd(Command *);

bool exec_built_ins(Command *);

int built_in_count();

#endif