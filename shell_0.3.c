#define _GNU_SOURCE  /* Ensure that getline is declared */
#include <stdio.h>   /* For standard I/O operations like getline */
#include <stdlib.h>  /* For memory management like malloc and free */
#include <string.h>
#include <unistd.h>  /* For system calls like fork, execve, access */
#include <sys/types.h> /* For types like pid_t */
#include <sys/wait.h> /* For wait functions */
#include <sys/stat.h> /* For stat functions */

#define MAX_ARGS 100 /* Define the maximum number of arguments */
#define PATH_MAX 4096 /* Maximum length for PATH */

static char *my_strtok_r(char *str, const char *delim, char **saveptr);

/** 
 * Function to calculate the length of a string.
 * @param str The string whose length is to be calculated.
 * @return The length of the string.
 */
size_t my_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

/** 
 * Function to copy a string.
 * @param dest The destination buffer where the string is to be copied.
 * @param src The source string to be copied.
 * @return A pointer to the destination buffer.
 */
char *my_strcpy(char *dest, const char *src) {
    char *ptr = dest;
    while ((*ptr++ = *src++) != '\0');
    return dest;
}

/** 
 * Function to concatenate two strings.
 * @param dest The destination buffer where the string is to be appended.
 * @param src The source string to be appended.
 * @return A pointer to the destination buffer.
 */
char *my_strcat(char *dest, const char *src) {
    char *ptr = dest + my_strlen(dest);
    while ((*ptr++ = *src++) != '\0');
    return dest;
}

/** 
 * Function to duplicate a string.
 * @param str The string to be duplicated.
 * @return A pointer to the duplicated string, or NULL on failure.
 */
char *my_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = my_strlen(str) + 1;
    char *copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    my_strcpy(copy, str);
    return copy;
}

/**
 * Function to tokenize a string, similar to strtok.
 * @param str The string to be tokenized.
 * @param delim The delimiter string.
 * @return A pointer to the next token, or NULL if there are no more tokens.
 */
char *my_strtok(char *str, const char *delim) {
    static char *saveptr;
    return my_strtok_r(str, delim, &saveptr);
}

/**
 * Reentrant version of my_strtok.
 * @param str The string to be tokenized.
 * @param delim The delimiter string.
 * @param saveptr A pointer to a char* variable that stores the current position in the string.
 * @return A pointer to the next token, or NULL if there are no more tokens.
 */
static char *my_strtok_r(char *str, const char *delim, char **saveptr) {
    char *end;

    if (str == NULL) {
        str = *saveptr;
    }

    if (*str == '\0') {
        *saveptr = str;
        return NULL;
    }

    /* Scan leading delimiters */
    str += strspn(str, delim);
    if (*str == '\0') {
        *saveptr = str;
        return NULL;
    }

    /* Find the end of the token */
    end = str + strcspn(str, delim);
    if (*end == '\0') {
        *saveptr = end;
        return str;
    }

    /* Terminate the token and make saveptr point to the next character */
    *end = '\0';
    *saveptr = end + 1;
    return str;
}

/** 
 * Function to split the input string into arguments.
 * @param input The input string to be split.
 * @param args The array to store the split arguments.
 * @return The number of arguments parsed.
 */
int parse_args(char *input, char *args[]) {
    int count = 0;
    char *token = my_strtok(input, " \n"); /* Tokenize input by spaces and newlines */
    while (token != NULL && count < MAX_ARGS - 1) {
        args[count++] = token; /* Store the token in the args array */
        token = my_strtok(NULL, " \n"); /* Get the next token */
    }
    args[count] = NULL; /* Null-terminate the array */
    return count; /* Return the number of arguments parsed */
}

/** 
 * Function to find the full path of a command.
 * @param command The command to find.
 * @param path The PATH environment variable.
 * @return The full path of the command if found, NULL otherwise.
 */
char *find_command_path(const char *command, const char *path) {
    char *path_copy = my_strdup(path);
    if (path_copy == NULL) {
        perror("my_strdup");
        return NULL;
    }

    char *dir = my_strtok(path_copy, ":");
    while (dir != NULL) {
        char full_path[PATH_MAX];
        full_path[0] = '\0'; /* Initialize full_path to an empty string */
        my_strcat(full_path, dir);
        my_strcat(full_path, "/");
        my_strcat(full_path, command);

        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return my_strdup(full_path); /* Return a copy of the found path */
        }
        dir = my_strtok(NULL, ":");
    }

    free(path_copy);
    return NULL; /* Command not found in PATH */
}

int main(int ac, char **av) {
    char *input = NULL;  /* Pointer to store the input string */
    size_t input_len = 0; /* Variable to store the length of the input string */
    int i = 0; /* Variable for looping through arguments */
    char *args[MAX_ARGS]; /* Array to store parsed arguments */
    char *path = getenv("PATH"); /* Get the PATH environment variable */
    char *command_path;

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

        /* Read the input line from stdin using getline */
        ssize_t read = getline(&input, &input_len, stdin);

        if (read == -1) /* Check if reading the line failed */
        {
            free(input); /* Free the allocated memory */
            printf("The program failed to read the line or was interrupted\n");
            return (1);  /* Exit the program with an error code */
        }
        else
        {
            /* Parse the input into arguments */
            int num_args = parse_args(input, args);
            
            /* Skip empty input or commands */
            if (num_args == 0) {
                continue;
            }

            /* Find the command path */
            command_path = find_command_path(args[0], path);
            if (command_path == NULL) {
                printf("Command not found: %s\n", args[0]);
                continue;
            }

            pid_t pid = fork(); /* Create a child process */
            if (pid == -1) {
                perror("fork");
                free(input);
                free(command_path);
                return (1);
            }

            if (pid == 0) {
                /* Child process */
                execve(command_path, args, NULL);
                perror("execve");
                free(input);
                free(command_path);
                _exit(1);
            } else {
                /* Parent process */
                wait(NULL); /* Wait for the child process to finish */
                free(command_path);
            }
        }
    }

    /* Clean up */
    free(input); /* Free the allocated memory */
    return 0;
}

