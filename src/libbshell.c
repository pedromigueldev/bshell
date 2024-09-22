#include "libbshell.h"

int print() {
    printf("Testing bshell!!\n");
    return 1;
}

int (*shell_bultin_functions[]) (char **) = {
    &print
};

char *shell_bultin_named_functions[] = {
  "print"
};

int shell_num_builtins()
{
  return sizeof(shell_bultin_named_functions) / sizeof(char *);
}

int add_funtion_to_builtins(char* name, int (*function)(char**))
{
    int i = shell_num_builtins();
    shell_bultin_named_functions[i] = name;
    shell_bultin_functions[i] = function;
    return 1;
}

int _execute(char** args)
{

    if (args[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < shell_num_builtins(); i++)
    {
        if (strcmp(args[0], shell_bultin_named_functions[i]) == 0)
        {
            return (*shell_bultin_functions[i])(args);
        }

    }

    printf("Funtion not found!\n");
    return 1;
}

int shell_main(){
    char* line;
    char** args;
    int status = 1;

    do {
        printf("Type for exemple \"print\"\n");

        line = _get_item();
        args = _split_line(line);
        status = _execute (args);
    } while (status);

    return status;
}
