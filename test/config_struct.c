#include <criterion/criterion.h>
#include "../src/libbshell.h"

Test(config_struct, create) {
    ConfigStruct config_struct = bshell_config_init();
    cr_expect(config_struct.add_extra_f != NULL, "It should init correctly the config_struct.");
}
