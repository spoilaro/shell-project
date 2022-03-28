#ifndef _PROMPTH_
#define _PROMPTH_

#define MAX_ARG_COUNT 10
#define ERRMSG "An error has occurred\n"
#define MAX_PATH_LEN 256

#include <stdbool.h>
#include "command.h"


char *prompt(void);

bool exec_command(Command *, char *);


#endif
