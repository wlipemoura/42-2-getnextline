/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/16 23:22:59 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Garanta que sua função se comporta bem tanto lendo um arquivo quanto  
//lendo um input padrão.

//Seu programa precisa compilar com a flag -D BUFFER_SIZE=xx, que 
//será usada como o tamanho do buffer
//a ser lido na sua função get_next_line: 
//gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c

//Cada vez que você encontrar uma linha, você deve retornar a linha atual.

//Sua função ainda funciona quando o BUFFER_SIZE é 9999? E 1?

//Try to read from a file, from a redirection, from standard input. 
//How does your program behave when you send a
//newline to the standard output? And CTRL-D?

//7. Se a leitura não foi bem sucedida (read = 0), 
//faça uma maracutaia que não sei o que é
#include "get_next_line.h"


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cont;

	cont = 0;
	while (*(s1 + cont) && *(s2 + cont)
		&& cont < (n - 1)
		&& (*(s1 + cont) == *(s2 + cont)))
		cont++;
	if ((*(s1 + cont) != *(s2 + cont) && n))
		return (*(unsigned char *)(s1 + cont) - *(unsigned char *)(s2 + cont));
	return (0);
}

char	*ft_strjoin_and_free(char **s1, char **s2, int return_flag)
{
	char	*newstring;
	int		lens1;
	int		lens2;

	lens1 = ft_strlen (*s1);
	lens2 = ft_strlen (*s2);
	newstring = ft_calloc ((lens1 + lens2 + 1), sizeof (char));
	if (!newstring)
		return (NULL);
	ft_memmove(newstring, *s1, lens1);
	ft_memmove(newstring + lens1, *s2, lens2);
	free(*s2);
	*s2 = NULL;
	free(*s1);
	*s1 = NULL;
	if (return_flag)
	{
		free(newstring);
		newstring = NULL;
	}
	return (newstring);
}

char	*breakline_found(char **line, char *auxiliar)
{
	size_t	index;
	char	*missed_buffer;
	char	*ptr;
	char	*unecessary;

	index = 0;
	unecessary = NULL;
	while (*(*line + index) != '\n')
		++index;
	ptr = *(line) + index + 1;
	free(auxiliar);
	auxiliar = ft_calloc(ft_strlen(*line) - ft_strlen(ptr) + 1, sizeof(char));
	ft_memmove(auxiliar, *line, ft_strlen(*line) - ft_strlen(ptr));
	if (ft_strncmp(*line, auxiliar, ft_strlen(*line)) == 0)
		ft_strjoin_and_free(line, &unecessary, 1);
	else
	{
		missed_buffer = ft_calloc(ft_strlen(*line) - index + 1, sizeof(char));
		ft_memmove(missed_buffer, ptr, ft_strlen(*line) - index);
		free(*line);
		*line = ft_strjoin_and_free(&missed_buffer, &unecessary, 0);
	}
	return (auxiliar);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*auxiliar;
	int			end_file_identifier;

	end_file_identifier = 1;
	auxiliar = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	end_file_identifier = read(fd, auxiliar, BUFFER_SIZE);
	if (fd < 0 || (!*auxiliar && !line) || !auxiliar || read(fd, auxiliar, 0))
		return (ft_strjoin_and_free(&auxiliar, &auxiliar, 1));
	if (line && *auxiliar)
		line = ft_strjoin_and_free(&line, &auxiliar, 0);
	else if (*auxiliar)
		line = ft_strjoin_and_free(&auxiliar, &line, 0);
	if (line && ft_strchr(line, '\n'))
		return (breakline_found(&line, auxiliar));
	else if (end_file_identifier == 0 && line)
		return (ft_strjoin_and_free(&line, &auxiliar, 0));
	return (get_next_line(fd));
}

// int	main (void)
// {
// 	int	fd_r;
// 	fd_r = open("file_r.txt",O_RDONLY);
// 	char *variavel_r;

// 	variavel_r = get_next_line(fd_r);
// 	//printf("O TEXTO É: %s", variavel);
// 	while(variavel_r)
// 	{
// 		printf("O TEXTO CERTO É: %s", variavel_r);
// 		free(variavel_r);
// 		variavel_r = get_next_line(fd_r);
// 	}
// 	free(variavel_r);
// 	return (0);
// }

// int	main (void)
// {
// 	int	fd_w;
// 	int	fd_r;
// 	fd_w = open("file_w.txt",O_RDONLY);
// 	fd_r = open("file_r.txt",O_RDONLY);
// 	char *variavel_w;
// 	char *variavel_r;

// 	variavel_w = get_next_line_w(fd_w);
// 	variavel_r = get_next_line_r(fd_r);
// 	//printf("O TEXTO É: %s", variavel);
// 	while(variavel_w && variavel_r)
// 	{
// 		printf("O TEXTO ERRADO É: %s", variavel_w);
// 		free(variavel_w);
// 		variavel_w = get_next_line_w(fd_w);
// 		printf("O TEXTO CERTO É: %s", variavel_r);
// 		free(variavel_r);
// 		variavel_r = get_next_line_r(fd_r);
// 	}
// 	free(variavel_w);
// 	free(variavel_r);
// 	return (0);
// }
