#include "get_next_line.h"

int	main (void)
{
	int	fd_r;
	fd_r = open("file_r.txt",O_RDONLY);
	char *variavel_r;

	variavel_r = get_next_line(fd_r);
	//printf("O TEXTO É: %s", variavel);
	while(variavel_r)
	{
		printf("O TEXTO CERTO É: %s", variavel_r);
		free(variavel_r);
		variavel_r = get_next_line(fd_r);
	}
	free(variavel_r);
	return (0);
}
