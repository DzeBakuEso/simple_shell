#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> /* Added for perror and printf */
#include <stdlib.h> /* Added for exit */

/**
 * main - Fork and wait example
 *
 * Description: This program forks a child process and waits for it to finish.
 * The child process executes the command "/bin/ls -l /usr".
 *
 * Return: Always 0 (Success).
 */
int main(void)
{
        pid_t child_pid;
        int status;
        int count = 0; /* Initialize the counter */

        while (count < 5) /* Loop to create 5 child processes */
        {
                child_pid = fork(); /* Create a new child process */

                if (child_pid == -1) /* Error handling if fork fails */
                {
                        perror("Fork failed");
                        exit(EXIT_FAILURE); /* Exit if fork fails */
                }

                if (child_pid == 0) /* Child process */
                {
                        char *argv[] = {"/bin/ls", "-l", "/usr", NULL};

                        if (execve(argv[0], argv, NULL) == -1) /* Execute command */
                        {
                                perror("Error executing execve");
                                exit(EXIT_FAILURE); /* Exit if execve fails */
                        }
                }
                else /* Parent process */
                {
                        wait(&status); /* Wait for child process to finish */
                        printf("Child process %d finished\n", child_pid);
                        printf("Oh, it's all better now\n");
                }

                count++; /* Increment the counter */
        }

        return (0);
}

