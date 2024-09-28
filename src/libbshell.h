#ifndef __BSHELL_H__
#define __BSHELL_H__

#include "libbshell_string.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    char* name;
    int (*extra_function)(char**);
} ExtraFunction;

typedef struct {
    char* wellcome_message;
    char* prompt;
} ConfigStruct;

int shell_main(ConfigStruct* config);
int print_funtion_list();
int add_extra_function(char* name, int (*function)(char**));

#endif
