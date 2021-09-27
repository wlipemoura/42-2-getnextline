/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/27 09:08:22 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
