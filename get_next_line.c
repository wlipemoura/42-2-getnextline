/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/15 01:36:37 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Garanta que sua função se comporta bem tanto lendo um arquivo quanto lendo um input padrão.

//Seu programa precisa compilar com a flag -D BUFFER_SIZE=xx, que será usada como o tamanho do buffer
//a ser lido na sua função get_next_line: gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c

//Cada vez que você encontrar uma linha, você deve retornar a linha atual.

//Sua função ainda funciona quando o BUFFER_SIZE é 9999? E 1?

//Try to read from a file, from a redirection, from standard input. How does your program behave when you send a
//newline to the standard output? And CTRL-D?

//7. Se a leitura não foi bem sucedida (read = 0), faça uma maracutaia que não sei o que é
#include "get_next_line.h"

char	*breakline_founded(char **line_that_is_be_readen, char *auxiliar)
{
	size_t	index;
	char	*missed_buffer;
	char	*ponteiro;

	index = 0;
	while (*(*line_that_is_be_readen + index) != '\n')
		++index;
	ponteiro = *(line_that_is_be_readen) + index + 1;
	auxiliar = ft_calloc(ft_strlen(*line_that_is_be_readen) - ft_strlen(ponteiro) + 1, sizeof(char));
	ft_memmove(auxiliar, *line_that_is_be_readen, ft_strlen(*line_that_is_be_readen) - ft_strlen(ponteiro));
	if (ft_strncmp(*line_that_is_be_readen, auxiliar, ft_strlen(*line_that_is_be_readen)) == 0)
	{
		free(*line_that_is_be_readen);
		*line_that_is_be_readen = NULL;
		return (auxiliar);
	}
	else
	{
		missed_buffer = ft_strdup_modified(ponteiro);
		free(*line_that_is_be_readen);
		*line_that_is_be_readen = ft_strdup_modified(missed_buffer);
		free(missed_buffer);
	}
	return (auxiliar);
}

void	freed_and_nulled(char **string)
{
	free(*string);
	*string = NULL;
	return ;
}

char	*get_next_line(int fd)
{
	static char	*line_that_is_be_readen = NULL;
	char		*auxiliar;
	int			end_file_identifier;

	auxiliar = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	end_file_identifier = read(fd, auxiliar, BUFFER_SIZE);
	if (fd < 0 || (!*auxiliar && !line_that_is_be_readen) || !auxiliar || read(fd, auxiliar, 0))
	{
		freed_and_nulled(&auxiliar);
		return (NULL);
	}
	if (line_that_is_be_readen && *auxiliar)
		line_that_is_be_readen = ft_strjoin_modified(&line_that_is_be_readen, &auxiliar);
	else if (*auxiliar)
		line_that_is_be_readen = ft_strdup_modified(auxiliar);
	freed_and_nulled(&auxiliar);
	if (line_that_is_be_readen && ft_strchr(line_that_is_be_readen, '\n'))
		return (breakline_founded(&line_that_is_be_readen, auxiliar));
	else if (end_file_identifier == 0 && line_that_is_be_readen)
	{
		auxiliar = ft_strdup_modified(line_that_is_be_readen);
		freed_and_nulled(&line_that_is_be_readen);
		return (auxiliar);
	}
	return (get_next_line(fd));
}
/*
int	main (void)
{
	int	fd;
	fd = open("file.txt",O_RDONLY);
	char *variavel;

	variavel = get_next_line(fd);
	printf("O TEXTO É: %s", variavel);
	// while(variavel)
	// {
	// 	printf("O TEXTO É: %s", variavel);
	// 	free(variavel);
	// 	variavel = get_next_line(fd);
	// }
	free(variavel);
	return (0);
}*/
