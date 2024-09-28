#include "libbshell.h"
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

    int i = 0;
    for (;; i++) {
        if (shell_bultin_named_functions[i] == NULL) {
            return i;
        }
    }

  // return sizeof(shell_bultin_named_functions) / sizeof(char *);
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
        // printf("Comparing %s with %s: theres %d args\n", args[0], shell_bultin_named_functions[i], shell_num_builtins());
        if (strcmp(args[0], shell_bultin_named_functions[i]) == 0)
        {
            return (*shell_bultin_functions[i])(args);
        }

    }
    printf("Funtion not found!\n");
    return 1;
}

int _exit_shell (char** arg) {
    for (int i = 0; i < shell_num_builtins(); i++) {
        free(shell_bultin_named_functions[i]);
    }
    free(shell_bultin_functions);
    free(shell_bultin_named_functions);
    return 0;
}

int add_extra_function(char* name, int (*function)(char**)){
    int count = shell_num_builtins();
    int amount = count + 1;

    if (shell_bultin_functions == NULL || shell_bultin_named_functions == NULL) {
        shell_bultin_functions = malloc(amount * sizeof(int (*)(char**)));
        shell_bultin_named_functions = malloc(amount * sizeof(char*));
    } else {
        shell_bultin_functions = realloc(shell_bultin_functions, (amount + 1) * sizeof(int (*)(char**)));
        shell_bultin_named_functions = realloc(shell_bultin_named_functions, (amount + 1) * sizeof(char*));

        if (shell_bultin_functions == NULL || shell_bultin_named_functions == NULL) {
            fprintf(stderr,"Unable to grow token size");
            exit(EXIT_FAILURE);
        }
    }

    shell_bultin_named_functions[count] = strdup(name);
    shell_bultin_functions[count] = function;
    return 1;
}

int shell_main(ConfigStruct* config){
    char* line;
    char** args;
    int status = 1;

    if (config) {
        default_config = *config;
    }

    add_extra_function("exit", _exit_shell);

    printf("%s\n", default_config.wellcome_message);
    do {
        printf("%s", default_config.prompt);

        line = _get_item();
        args = _split_line(line);
        status = _execute (args);
    } while (status);

    free(args);
    free(line);
    return status;
}
