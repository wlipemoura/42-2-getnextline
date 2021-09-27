/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/27 08:44:49 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*line[OPEN_MAX + 1];
	char		*auxiliar;
	int			end_file_identifier;

	end_file_identifier = 1;
	auxiliar = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	end_file_identifier = read(fd, auxiliar, BUFFER_SIZE);
	if (fd < 0 || !auxiliar || read(fd, auxiliar, 0) || BUFFER_SIZE <= 0)
		return (ft_strjoin_and_free(&auxiliar, &auxiliar, 1));
	if (*(line + fd) && *auxiliar)
		*(line + fd) = ft_strjoin_and_free((line + fd), &auxiliar, 0);
	else if (*auxiliar)
		*(line + fd) = ft_strjoin_and_free(&auxiliar, (line + fd), 0);
	if (*(line + fd) && ft_strchr(*(line + fd), '\n'))
		return (breakline_found((line + fd), auxiliar));
	if (end_file_identifier == 0 && *(line + fd))
		return (ft_strjoin_and_free((line + fd), &auxiliar, 0));
	else if (end_file_identifier == 0)
		return (ft_strjoin_and_free((line + fd), &auxiliar, 1));
	return (get_next_line(fd));
}

// int	main (void)
// {
// 	int	fd_r;
// 	fd_r = open("file_r.txt",O_RDONLY);
// 	char *variavel_r;

// 	variavel_r = get_next_line(fd_r);
// 	// printf("O TEXTO É: %s", variavel_r);
// 	while(variavel_r)
// 	{
// 		printf("O TEXTO CERTO É: %s", variavel_r);
// 		free(variavel_r);
// 		variavel_r = get_next_line(fd_r);
// 	}
// 	free(variavel_r);
// 	// variavel_r = get_next_line(fd_r);
// 	// printf("O TEXTO É: %s", variavel_r);
// 	// free(variavel_r);
// 	// printf("O TEXTO É: %s", variavel_r);
// 	// free(variavel_r);
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
