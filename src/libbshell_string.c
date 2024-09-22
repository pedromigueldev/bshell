#include "libbshell_string.h"

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
