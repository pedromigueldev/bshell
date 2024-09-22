#include "libbshell.h"

int print() {
    printf("Testing bshell!!\n");
    return 1;
}

int (*dotto_bultin_functions[]) (char **) = {
    &print
};

char *dotto_bultin_named_functions[] = {
  "print"
};

int dotto_num_builtins()
{
  return sizeof(dotto_bultin_named_functions) / sizeof(char *);
}

int _execute(char** args)
{

    if (args[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < dotto_num_builtins(); i++)
    {
        if (strcmp(args[0], dotto_bultin_named_functions[i]) == 0)
        {
            return (*dotto_bultin_functions[i])(args);
        }

    }

    printf("Funtion not found!\n");
    return 1;
}

char* _get_item()
{
    int position = 0;
    char character;
    int buffer_size = BSHELL_LINE_BUFFER_SIZE;
    char* buffer = malloc(sizeof(char)*buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Failed to alocate memory\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        character = getchar();

        if (character == EOF || character == '\n' || position >= buffer_size) {
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position] = character;
        position++;

        if (position >= buffer_size) {
            buffer_size += BSHELL_LINE_BUFFER_SIZE;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) {
                fprintf(stderr, "Dotto: reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return buffer;
}

char** _split_line(char* line)
{
    int buffer_size = BSHELL_ARG_BUFFER_SIZE, position = 0;
    char** tokens = malloc(buffer_size * sizeof(char*));
    char* token;

    if (tokens == NULL)
    {
        fprintf(stderr,"Unable to allocate for tokens");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, BSHELL_TOKEN_DELIM );

    while (token != NULL) {

        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
            buffer_size += BSHELL_ARG_BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char*));

            if (tokens == NULL) {
                fprintf(stderr,"Unable to grow token size");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, BSHELL_TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
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
