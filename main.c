#include "./src/libbshell.h"

int print1() {
    printf("Print 22\n");
    return 1;
}

int main() {
    ConfigStruct config_struct = bshell_config_init();
    config_struct.wellcome_message = "TESTING SHELL";
    config_struct.prompt = "HELLOS: ";
    config_struct.add_extra_f("print1", &print1);

    return bshell_main(config_struct);
}
