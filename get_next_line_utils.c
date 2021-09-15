/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:25 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/14 21:15:14 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	cont;

	cont = 0;
	if (!src && !dest && n > 0)
		return (NULL);
	if (src > dest)
	{
		while (cont < n)
		{
			*(unsigned char *)(dest + cont) = *(unsigned char *)(src + cont);
			cont++;
		}
	}
	else
	{
		while (n != 0)
		{
			*(unsigned char *)(dest + n - 1) = *(unsigned char *)(src + n - 1);
			n--;
		}
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	char	*string;

	string = (char *)s;
	while (*string)
	{
		if (*string != (char) c)
			string++;
		else
			return (string);
	}
	if (*string == (char) c)
		return (string);
	else
		return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (*(s + counter))
		counter++;
	return (counter);
}

//Lembre-se de testar essa calloc: você a modificou para eliminar a bzero
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	finalsize;
	size_t	cont;

	finalsize = nmemb * size;
	p = malloc (finalsize);
	cont = 0;
	if (!p)
		return (NULL);
	while (cont < finalsize)
	{
		*(char *)(p + cont) = '\0';
		cont++;
	}
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	substring_length;

	if (!s)
	{
		substring = ft_calloc(1, sizeof(char));
		ft_memmove(substring, "", 1);
		return (substring);
	}
	if (start > ft_strlen(s))
		substring_length = 0;
	else
	{
		substring_length = ft_strlen(s + start);
		if (substring_length > len)
			substring_length = len;
	}
	substring = ft_calloc(substring_length + 1, sizeof(char));
	if (substring == NULL)
		return (NULL);
	ft_memmove(substring, s + start, substring_length);
	return (substring);
}

char	*ft_strjoin_modified(char *s1, char *s2)
{
	char	*newstring;
	int		lens1;
	int		lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen (s1);
	lens2 = ft_strlen (s2);
	newstring = ft_calloc ((lens1 + lens2 + 1), sizeof (char));
	if (!newstring)
		return (NULL);
	ft_memmove (newstring, s1, lens1);
	ft_memmove (newstring + lens1, s2, lens2);
	free(s1);//Here is the modification
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (newstring);
}

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

char	*ft_strdup_modified(char *s)
{
	char	*new_string;
	size_t	length;

	length = ft_strlen(s) + 1;
	new_string = ft_calloc(length, sizeof(char));
	if (!new_string)
		return (NULL);
	ft_memmove(new_string, s, length);
	return (new_string);
}
