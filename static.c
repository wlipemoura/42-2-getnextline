#include <unistd.h>
#include <stdio.h>

int	add(int x)
{
	static int	sum = 0;
	sum += x;
	return (sum);
}

int	main(int argc, char **argv)
{
	printf("%d\n", add(5));
	printf("%d\n", add(5));
	printf("%d\n", add(5));
	return (0);
}