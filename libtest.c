#include "./src/libbshell.h"
#include <stdio.h>

int print1() {
    printf("Print 22\n");
    return 1;
}

int print2() {
    printf("print 2");
    return 1;
}

int print3 () {
    printf("orint3");
    return 1;
}

int print4() {
    printf("print4");
    return 1;
}
int main() {
    ConfigStruct config_struct = {
        .wellcome_message = "Welcome to the shell",
        .prompt = "bshell> "
    };
    add_extra_function("print1", &print1);
    add_extra_function("print2", &print2);
    add_extra_function("print3", &print3);
    add_extra_function("print4", &print4);

    return shell_main(&config_struct);
}
