#include <criterion/criterion.h>
#include "../src/libbshell.h"

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

Test(add_extra_function, adding) {
    ConfigStruct config_struct = bshell_config_init();

    cr_expect(config_struct.add_extra_f("print1", &print1) == 1, "It should return 1 if addded successfully in the array.");
    cr_expect(config_struct.add_extra_f("print2", &print2) == 1, "It should return 1 if addded successfully in the array.");
    cr_expect(config_struct.add_extra_f("print2", &print2) == 1, "It should return 1 if addded successfully in the array.");
}
