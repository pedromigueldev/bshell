#ifndef __BSHELL_H__
#define __BSHELL_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BSHELL_LINE_BUFFER_SIZE 1024
#define BSHELL_ARG_BUFFER_SIZE 64
#define BSHELL_TOKEN_DELIM "\t\r\n\a:"

int shell_main();
char* _get_item();
char** _split_line(char* line);
int _execute(char** args);

#endif