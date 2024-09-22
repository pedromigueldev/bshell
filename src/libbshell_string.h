#ifndef __BSHELL_STRING__
#define __BSHELL_STRING__

#define BSHELL_LINE_BUFFER_SIZE 1024
#define BSHELL_ARG_BUFFER_SIZE 64
#define BSHELL_TOKEN_DELIM "\t\r\n\a:"

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char* _get_item();
char** _split_line(char* line);

#endif
