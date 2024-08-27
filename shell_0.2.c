#include <stdio.h>   /* Standard input/output library */
#include <stdlib.h>  /* Standard library for memory allocation */
#include <string.h>  /* String handling library */

#define MAX_LINE_LENGTH 1024 /* Define the maximum length for the input line */
#define MAX_ARGS 100 /* Define the maximum number of arguments */

/** 
 * Function to read a line of input from stdin.
 * @param lineptr Pointer to a buffer where the input will be stored.
 * @param n Pointer to the size of the buffer.
 * @param stream Input stream to read from.
 * @return The number of characters read, or -1 on failure.
 */
size_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return (size_t)-1;
    }

    size_t length = 0;
    char *buffer = NULL;
    int c;

    /* Allocate memory for the buffer if not already allocated */
    if (*lineptr == NULL) {
        *lineptr = malloc(MAX_LINE_LENGTH);
        if (*lineptr == NULL) {
            return (size_t)-1;
        }
        *n = MAX_LINE_LENGTH;
    }

    buffer = *lineptr;

    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= *n) {
            *n *= 2;
            buffer = realloc(buffer, *n);
            if (buffer == NULL) {
                return (size_t)-1;
            }
            *lineptr = buffer;
        }
        buffer[length++] = c;
    }

    if (length == 0 && c == EOF) {
        return (size_t)-1; /* No input read and EOF encountered */
    }

    buffer[length] = '\0'; /* Null-terminate the buffer */
    return length;
}

/** 
 * Function to split the input string into arguments.
 * @param input The input string to be split.
 * @param args The array to store the split arguments.
 * @return The number of arguments parsed.
 */
int parse_args(char *input, char *args[]) {
    int count = 0;
    char *token = strtok(input, " \n"); /* Tokenize input by spaces and newlines */
    while (token != NULL && count < MAX_ARGS - 1) {
        args[count++] = token; /* Store the token in the args array */
        token = strtok(NULL, " \n"); /* Get the next token */
    }
    args[count] = NULL; /* Null-terminate the array */
    return count; /* Return the number of arguments parsed */
}

int main(int ac, char **av) {
    char *input = NULL;  /* Pointer to store the input string */
    size_t input_len = 0; /* Variable to store the length of the input string */
    size_t read;  /* Variable to store the number of characters read */
    int i = 0; /* Variable for looping through arguments */
    char *args[MAX_ARGS]; /* Array to store parsed arguments */

    /* Print the number of arguments passed */
    printf("The argument count is %d\n", ac);

    /* Print the first argument (the program name) */
    printf("The first argument is %s\n", av[0]);

    /* Loop through and print all arguments */
    while (av[i] != NULL) {
        printf("%d : %s\n", i + 1, av[i]);
        i++;
    }

    while (1) /* Infinite loop to keep prompting for input */
    {
        printf("cmd: "); /* Print the command prompt */

        /* Read the input line from stdin */
        read = my_getline(&input, &input_len, stdin);

        if (read == (size_t)-1) /* Check if reading the line failed */
        {
            free(input); /* Free the allocated memory */
            printf("The program failed to read the line or was interrupted\n");
            return (1);  /* Exit the program with an error code */
        }
        else
        {
            /* Parse the input into arguments */
            int num_args = parse_args(input, args);
            
            /* Print the parsed arguments */
            printf("You entered %d arguments:\n", num_args);
            int j;
            for (j = 0; j < num_args; j++) {
                printf("%d : %s\n", j + 1, args[j]);
            }
        }
    }

    /* Clean up */
    free(input); /* Free the allocated memory */
    return 0;
}

