#include <stdio.h>

int main(int ac, char **av)
{
        int i = 0;

        /* Print the number of arguments passed */
        printf("The argument count is %d\n", ac);

        /* Print the first argument (the program name) */
        printf("The first argument is %s\n", av[0]);

        /* Loop through and print all arguments */
        while (av[i] != NULL)
        {
                printf("%d : %s\n", i + 1, av[i]);
                i++;
        }

        return (0);
}

