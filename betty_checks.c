#include<stdio.h>

/** 
 * add - adds two integers
 * @a: First integer
 * @b: Second integer
 *
 * Return: The sum of a and b
 *
 */
int add(int a, int b)
{
	return (a + b);

}

/**
 * main - Entry point of the Program
 *
 * Return: Always 0 (success)
 */

int main(void)
{
	int result;

	result = add(37, 87);
	printf("The sum of the nubers is: %d\n", result);
	return (0);
}
