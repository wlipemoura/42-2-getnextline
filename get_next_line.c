/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/13 21:55:48 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Se não há nada para ler, retorna nulo.

//Garanta que sua função se comporta bem tanto lendo um arquivo quanto lendo um input padrão.

//Seu programa precisa compilar com a flag -D BUFFER_SIZE=xx, que será usada como o tamanho do buffer
//a ser lido na sua função get_next_line: gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c.

//Cada vez que você encontrar uma linha, você deve retornar a linha atual.

//Sua função ainda funciona quando o BUFFER_SIZE é 9999? E 1?

//Try to read from a file, from a redirection, from standard input. How does your program behave when you send a
//newline to the standard output? And CTRL-D?

//7. Se a leitura não foi bem sucedida (read = 0), faça uma maracutaia que não sei o que é
#include "get_next_line.h"

char *buffer_saver(char	*line_that_is_be_readen, int index)
{
	char *missed_buffer;

	missed_buffer = ft_strdup_modified(line_that_is_be_readen + index + 1);
	free(line_that_is_be_readen);
	return (missed_buffer);
}

char we_found_a_breakline(...)
{
	
}

char *get_next_line(int fd)
{
	static char	*line_that_is_be_readen = NULL;
	char 		*auxiliar;
	size_t		index;
	int			end_file_identifier;//essa é só uma forma de identificar que foi a última leitura do arquivo.

	end_file_identifier = 1;
while (end_file_identifier > 0)
{
	index = 0;
	auxiliar = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	end_file_identifier = read(fd, auxiliar, BUFFER_SIZE);
	if (line_that_is_be_readen)
		line_that_is_be_readen = ft_strjoin_modified(line_that_is_be_readen, auxiliar);
	else if (*auxiliar)
	{
		line_that_is_be_readen = ft_strdup_modified(auxiliar);//dou free na auxiliar na própria dup
		free(auxiliar);
		auxiliar = NULL;
	}
	if (line_that_is_be_readen && ft_strchr(line_that_is_be_readen, '\n'))
	{
		index = 0;
		while(*(line_that_is_be_readen + index) != '\n')
			++index;
		auxiliar = ft_substr(line_that_is_be_readen, 0, (index + 1));
		if(ft_strncmp(line_that_is_be_readen, auxiliar, ft_strlen(line_that_is_be_readen)) == 0)
		{
			free(line_that_is_be_readen);
			line_that_is_be_readen = NULL;
			return (auxiliar);
		}
		else
		{
			line_that_is_be_readen = buffer_saver(line_that_is_be_readen, index);
			return (auxiliar);
		}
	}
	else if (end_file_identifier == 0)
	{
		if (*auxiliar == '\0')
			return (NULL);
		else
			return(auxiliar);
	}
	else
		continue ;
}
	return (NULL);
}

int	main (void)
{
	int	fd;
	int	times = 33;
	fd = open("file.txt",O_RDONLY);
	while(times)
	{
		printf("O TEXTO É: %s", get_next_line(fd));
		times--;
	}
	return (0);
}