#include "libbshell.h"
#include <complex.h>
#include <stdio.h>

ConfigStruct default_config = {
    .wellcome_message = "Welcome to the shell",
    .prompt = "bshell> "
};

int (**shell_bultin_functions) (char **);
char **shell_bultin_named_functions;

int shell_num_builtins()
{
    if (NULL == shell_bultin_named_functions) {
        return 0;
    }

  return sizeof(shell_bultin_named_functions) / sizeof(char *);
}

int set_config_struct(ConfigStruct config)
{
    default_config = config;
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
        // printf("Comparing %s with %s\n", args[0], shell_bultin_named_functions[i]);
        if (strcmp(args[0], shell_bultin_named_functions[i]) == 0)
        {
            return (*shell_bultin_functions[i])(args);
        }

    }
    printf("Funtion not found!\n");
    return 1;
}

int add_extra_function(char* name, int (*function)(char**)){
    int count = shell_num_builtins();
    int amount = count + 1;

    if (shell_bultin_functions == NULL || shell_bultin_named_functions == NULL) {
        shell_bultin_functions = malloc(amount * sizeof(int (*)(char**)));
        shell_bultin_named_functions = malloc(amount * sizeof(char*));
    }

    int (**old_functions)(char**) = malloc(amount * sizeof(int (*)(char**)));
    char** old_named_functions = malloc(amount * sizeof(char*));

    for (int i = 0; i < count; i++) {
        old_functions[i] = shell_bultin_functions[i];
        old_named_functions[i] = shell_bultin_named_functions[i];
    }

    old_named_functions[count] = strdup(name);
    old_functions[count] = function;

    shell_bultin_functions = old_functions;
    shell_bultin_named_functions = old_named_functions;
    return 1;
}

int shell_main(ConfigStruct* config){
    char* line;
    char** args;
    int status = 1;

    if (config) {
        default_config = *config;
    }

    if (shell_bultin_functions == NULL || shell_bultin_named_functions == NULL) {
        perror("Add a function to the shell before initializing");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", default_config.wellcome_message);
    do {
        printf("%s", default_config.prompt);

        line = _get_item();
        args = _split_line(line);
        status = _execute (args);
    } while (status);

    free(config);
    free(line);
    return status;
}
