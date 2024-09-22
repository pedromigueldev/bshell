#ifndef __BSHELL_H__
#define __BSHELL_H__

#include "libbshell_string.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    char* wellcome_message;
    char* prompt;

} ConfigStruct;

int shell_main();
int _execute(char** args);

#endif
