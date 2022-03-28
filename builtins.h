#ifndef _BUILTINSH_
#define _BUILTINSH_

#include <stdbool.h>

#include "prompt.h"

bool b_exit(Command *, char *);
bool b_cd(Command *, char *);

bool exec_built_ins(Command *, char *);

int built_in_count();

#endif