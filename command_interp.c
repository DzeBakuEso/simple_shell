#include <stdio.h>   /* Standard input/output library */
#include <stdlib.h>  /* Standard library for memory allocation */

int main(void)
{
    char *input = NULL;  /* Pointer to store the input string */
    size_t input_len = 0; /* Variable to store the length of the input string */
    int read;  /* Variable to store the number of characters read */

    while (1) /* Infinite loop to keep prompting for input */
    {
        printf("cmd: "); /* Print the command prompt */

        /* Read the input line from stdin */
        read = getline(&input, &input_len, stdin);

        if (read == -1) /* Check if reading the line failed */
        {
            free(input); /* Free the allocated memory */
            printf("The program failed to read the line or was interrupted\n");
            return (1);  /* Exit the program with an error code */
        }
        else
        {
            printf("%s\n", input); /* Print the input string */
            
            /* Uncomment these lines for additional debugging info */
            /* printf("The number of chars read is %d\n", read); */
            /* printf("The input was %s\n", input); */
        }

        free(input);  /* Free the allocated memory */
        input = NULL; /* Reset the pointer to NULL for the next iteration */
    }

    return (0); /* Return 0 to indicate successful execution */
}

