/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:19 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/27 12:44:56 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

/**
 * @brief read BUFFER_SIZE on a FD and return the line read until found a '\n'
 * or until the end of the file, if it doesn't find a '\n'. It can be called
 * more than once to read the following lines on the same file, until reach
 * the end of it.
 * 
 * @param fd is the File Descriptor associated to the reading.
 * 
 * @return the line read including '\n'.
 * @return NULL if the file is empty or an error occurred.
 */
char	*get_next_line(int fd);

/**
 * @brief copies 'n' bytes from the 'src' memory to the 'dest' memory.
 * The 'memmove' does behave correctly when dealing with overlap
 * (unlike memcpy.)
 * @param dest is a pointer to the destiny memory area.
 * @param src is a pointer to the source memory area.
 * @param n is the number of bytes it will be copied from 'src' to 'dest'.
 * 
 * @return a pointer to the 'dest' memory area.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief This function scans the string 's' searching for the 
 * character 'c'.
 *
 * @param s is a pointer to the string.
 * @param c is an integer that represents the searched character.
 *
 * @return a pointer to char: the first occurence of the 'c' character,
 * @return 'NULL' if the character is not found.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Calculate the length of string (excluding NULL character).
 *
 * @param s is a pointer to the string.
 *
* @return (size_t) the number of characters in the string pointed to by 's'.
 */
size_t	ft_strlen(const char *s);

/**
 * @brief allocates memory for an array of 'nmemb' elements 
 * of 'size' bytes each. The difference to 'malloc' function is that 'calloc'
 * function cleans the memory, giving to them the 'NULL' value.
 * 
 * @param nmemb the quantity of elements present in the array that needs memory.
 * @param size is the size, in bytes, of the element type from the array.
 * 
 * @return A pointer to the allocated memory.
 * @return 'NULL' if 'nmemb' or 'size' is equal to zero or if allocation
 * fails.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief compare two strings, s1 and s2, limited to compare only the first
 * (at most) 'n' bytes of s1 and s2.
 *
 * @param s1 is a pointer to the string 1 to be compared.
 * @param s2 is a pointer to the string 2 to be compared.
 * @param n is how many bytes will be analyzed in both strings.
 *
 * @return an integer less than zero if 's1' < 's2';
 * @return an integer greater than zero if 's1' > 's2';
 * @return 0 if the bytes analized match.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
