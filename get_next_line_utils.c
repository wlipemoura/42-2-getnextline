/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:25 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/27 09:10:57 by wfelipe-         ###   ########.fr       */
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
	if (!s)
		return (counter);
	while (*(s + counter))
		counter++;
	return (counter);
}

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
