/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:19 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/16 21:42:19 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
/**
 * @brief 
 * 
 * @param nptr 
 * 
 * @return the converted integer.
 */
char *get_next_line(int fd);

void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin_and_free(char **s1, char **s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s);
void	freed_and_nulled(char **string);

# endif
