#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LEN 1024

/** 
 * find_command_path - Find the full path of a command
 * @command: The command to search for
 *
 * Return: A pointer to the full path string or NULL if not found
 */
char *find_command_path(char *command)
{
    char *path = getenv("PATH"); /* Get the PATH environment variable */
    char *path_copy = strdup(path); /* Duplicate the PATH string */
    char *dir = strtok(path_copy, ":"); /* Tokenize PATH by ':' */
    char full_path[MAX_COMMAND_LEN]; /* Buffer to store the full command path */

    /* Loop through each directory in PATH */
    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0) /* Check if the command is executable */
        {
            free(path_copy);
            return strdup(full_path); /* Return the full path if found */
        }
        dir = strtok(NULL, ":"); /* Move to the next directory */
    }

    free(path_copy); /* Free the duplicated PATH string */
    return NULL; /* Return NULL if the command is not found */
}

/**
 * main - Simple shell implementation
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    pid_t child_pid; /* Process ID for the child process */
    int status; /* Status of the child process */
    char *input = NULL; /* Pointer to store user input */
    size_t input_len = 0; /* Length of the input */
    char *argv[MAX_COMMAND_LEN]; /* Array to store the command and its arguments */
    int i; /* Index for iterating through arguments */
    char *command_path; /* Variable to store the full command path */

    while (1)
    {
        printf("cmd: "); /* Display command prompt */

        /* Read user input */
        if (getline(&input, &input_len, stdin) == -1)
        {
            perror("Error reading line");
            break;
        }

        /* Remove newline character from input */
        input[strcspn(input, "\n")] = '\0';

        /* Tokenize input into command and arguments */
        i = 0;
        argv[i] = strtok(input, " ");
        while (argv[i] != NULL)
        {
            argv[++i] = strtok(NULL, " ");
        }

        if (argv[0] == NULL)
        {
            continue;  /* If input is empty, prompt again */
        }

        /* Find the full path of the command */
        command_path = find_command_path(argv[0]);
        if (command_path == NULL)
        {
            printf("Command not found or not executable: %s\n", argv[0]);
            continue;
        }

        /* Create a new child process */
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Fork failed");
            free(command_path);
            exit(EXIT_FAILURE);
        }

        /* In the child process, execute the command */
        if (child_pid == 0)
        {
            if (execve(command_path, argv, NULL) == -1)
            {
                perror("Error executing execve");
                free(command_path);
                exit(EXIT_FAILURE);
            }
        }
        else /* In the parent process, wait for the child to finish */
        {
            wait(&status);
            printf("Child process %d finished\n", child_pid);
        }

        free(command_path); /* Free the allocated memory for command path */
    }

    free(input); /* Free the allocated memory for user input */
    return (0); /* Return success */
}

