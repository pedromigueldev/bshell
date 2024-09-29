#ifndef __BSHELL_H__
#define __BSHELL_H__

#include "libbshell_string.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    char* wellcome_message;
    char* prompt;
    int (*add_extra_f)(char* name, int (*)(char**));
} ConfigStruct;

ConfigStruct bshell_config_init();
int shell_main(ConfigStruct config);
int add_extra_function(char* name, int (*function)(char**));

#endif
