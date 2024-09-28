#include "./src/libbshell.h"
#include <stdio.h>

int print1(char** nil) {
    printf("Print 22\n");
    return 1;
}

int main() {
    ConfigStruct config_struct = {
        .wellcome_message = "Welcome to the shell",
        .prompt = "bshell> "
    };
    add_extra_function("print1", &print1);

    return shell_main(&config_struct);
}
