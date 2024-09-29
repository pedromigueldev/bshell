#include "libbshell.h"
#include <stdio.h>

///* INTERNAL FUNCTIONS */ ------------------------------------------------------------------
static ConfigStruct default_config = {
    .wellcome_message = "Welcome to the shell",
    .prompt = "bshell> "
};

static int (**_bshell_functions) (char **);
static char **_bshell_functions_names;

static int _bshell_num_builtins()
{
    if (NULL == _bshell_functions_names) {
        return 0;
    }

    int i = 0;
    for (;; i++) {
        if (_bshell_functions_names[i] == NULL) {
            return i;
        }
    }

  // return sizeof(_bshell_functions_names) / sizeof(char *);
}

static int _execute(char** args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < _bshell_num_builtins(); i++)
    {
        // printf("Comparing %s with %s: theres %d args\n", args[0], _bshell_functions_names[i], _bshell_num_builtins());
        if (strcmp(args[0], _bshell_functions_names[i]) == 0)
        {
            return (*_bshell_functions[i])(args);
        }

    }
    printf("Funtion not found!\n");
    printf("The available functions are: \n");
    for (int i = 0; i < _bshell_num_builtins(); i++)
    {
        printf("%s\n", _bshell_functions_names[i]);
    }
    return 1;
}

static int _bshell_exit (char** arg) {
    for (int i = 0; i < _bshell_num_builtins(); i++) {
        free(_bshell_functions_names[i]);
    }
    free(_bshell_functions);
    free(_bshell_functions_names);
    return 0;
}

///* EXPOSED FUNCTIONS */ ------------------------------------------------------------------
ConfigStruct bshell_config_init () {
    ConfigStruct cn = {
        .wellcome_message = "Welcome to the Bshell",
        .prompt = "bshell> ",
        .add_extra_f = &add_extra_function
    };
    return cn;
}

int add_extra_function(char* name, int (*function)(char**)){
    int count = _bshell_num_builtins();
    int amount = count + 1;

    if (_bshell_functions == NULL || _bshell_functions_names == NULL) {
        _bshell_functions = malloc(amount * sizeof(int (*)(char**)));
        _bshell_functions_names = malloc(amount * sizeof(char*));

        if (_bshell_functions == NULL || _bshell_functions_names == NULL) {
            fprintf(stderr,"Unable to create memory for shell.\n");
            exit(EXIT_FAILURE);
            return 0;
        }
    } else {
        _bshell_functions = realloc(_bshell_functions, (amount + 1) * sizeof(int (*)(char**)));
        _bshell_functions_names = realloc(_bshell_functions_names, (amount + 1) * sizeof(char*));

        if (_bshell_functions == NULL || _bshell_functions_names == NULL) {
            fprintf(stderr,"Unable to grow shell memory\n");
            exit(EXIT_FAILURE);
            return 0;
        }
    }

    _bshell_functions_names[count] = strdup(name);
    _bshell_functions[count] = function;
    return 1;
}

int shell_main(ConfigStruct config){
    char* line;
    char** args;
    int status = 1;

    if (config.add_extra_f == NULL) {
        fprintf(stderr, "Config is not initialized.\n");
    }
    if (config.prompt && config.wellcome_message) {
        default_config = config;
    }

    add_extra_function("exit", _bshell_exit);

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
