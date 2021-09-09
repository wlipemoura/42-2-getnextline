/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2ndtry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/09 17:05:05 by wfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Lê o texto presente em um File Descriptor até que ele acabe?

//retorna a linha que acabou de ser lida.

//Se não há nada para ler, retorna nulo.

//Garanta que sua função se comporta bem tanto lendo um arquivo quanto lendo um input padrão.

//Seu programa precisa compilar com a flag -D BUFFER_SIZE=xx, que será usada como o tamanho do buffer
//a ser lido na sua função get_next_line: gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c.

//Cada vez que você encontrar uma linha, você deve retornar a linha atual.

//Sua função ainda funciona quando o BUFFER_SIZE é 9999? E 1?

//Try to read from a file, from a redirection, from standard input. How does your program behave when you send a
//newline to the standard output? And CTRL-D?

//TROQUE OS NOMES DAS VARIÁVEIS DA SPLIT!!!!

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

//Lembre-se de testar essa calloc: você a modificou
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	cont;

	cont = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (cont < n)
	{
		*(char *)(dest + cont) = *(char *)(src + cont);
		cont++;
	}
	return ((char *) dest);
}

char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	length;

	length = ft_strlen(s) + 1;
	new_string = malloc(length * sizeof(char));
	if (!new_string)
		return (NULL);
	ft_memcpy(new_string, s, length);
	return (new_string);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	counter;
	char	*substring;
	size_t	substring_length;

	counter = 0;
	if (!s)
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		substring_length = 0;
	else
	{
		substring_length = ft_strlen(s + start);
		if (substring_length > len)
			substring_length = len;
	}
	substring = (char *)malloc(substring_length + 1);
	if (substring == NULL)
		return (NULL);
	while (counter < substring_length)
	{
		*(substring + counter) = *(s + start + counter);
		counter++;
	}
	*(substring + counter) = '\0';
	return (substring);
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

char	*ft_strjoin(char const *s1, char const *s2)
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
	ft_memcpy (newstring, s1, lens1);
	ft_memcpy (newstring + lens1, s2, lens2);
	return (newstring);
}


//0. Verificar a posição do último caractere na variável ESTÁTICA por meio da strlen (se não houver nada, considerar 0).
//1. Calocar BUF bytes numa variável AUXILIAR
//2. Ler BUF bytes no fd e alocar na variável AUXILIAR
//2. Criar uma TERCEIRA variável a partir do join entre a ESTÁTICA e a AUXILIAR
//3. Free na ESTÁTICA
//4. Free na AUXILIAR
//5. Callocar na posição inicial da ESTÁTICA o comprimento da TERCEIRA string, gerada em 2
//6. Passar o conteúdo da TERCEIRA string para a variável ESTÁTICA
//7. Free na TERCEIRA string
//8. Verifique se há uma quebra de linha na variável ESTÁTICA usando strchr
//9. Se houver quebra:
//	9.1. verifique em qual posição está a quebra de linha usando strlen aplicada na ESTÁTICA (certamente é possível obter isso a partir do resultado do item 4 ao invés do strlen)
//	9.2. use essa informação e a substr para criar uma substring RETORNADA com o conteúdo a ser retornado.
//	9.3. use novamente strlen para obter a quantidade de memória necessária para alocar o conteúdo restante, após a quebra de linha, numa variável AUXILIAR. Use o resultado do passo 4 para obter a posição.
//	9.4. pegue a posição seguinte à quebra na ESTÁTICA e aloque todo o conteúdo a partir daí na variável AUXILIAR, usando memcpy por exemplo
//	9.6. free na ESTÁTICA
//	9.7. calloque na ESTÁTICA a mesma quantidade de memória callocada no item 9.3 (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
//	9.8. copie o conteúdo da string AUXILIAR, alocado em 9.4, para a ESTÁTICA (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
//	9.9. free na AUXILIAR (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra))
//	9.10. Retorne a string RETORNADA criada em 9.2.
//10. Se não houver quebra, mas eu chegar ao final do arquivo:
//	10.1. retorne a variável estática
//11. Se não houver quebra, mas eu não chegar ao final do arquivo:
//	11.1. vá para o passo 0.

//7. Se a leitura não foi bem sucedida (read = 0), faça uma maracutaia que não sei o que é



char *get_next_line(int fd)
{
	static char	*line_that_is_be_readen = NULL;
	char 		*auxiliar;
	char 		*joined_and_returned;
	size_t		index;
	int			end_file_identifier;//essa é só uma forma de identificar que foi a última leitura do arquivo.

	index = 0;
	joined_and_returned = NULL;
//1. Calocar BUF bytes numa variável AUXILIAR
	auxiliar = ft_calloc(BUFFER_SIZE, sizeof(char));
//2. Ler BUF bytes no fd e alocar na variável AUXILIAR
	end_file_identifier = read(fd, auxiliar, BUFFER_SIZE);
//2. Criar uma TERCEIRA variável a partir do join entre a ESTÁTICA e a AUXILIAR
	if (line_that_is_be_readen)
	{
		joined_and_returned = ft_strjoin(line_that_is_be_readen, auxiliar);
//3. Free na ESTÁTICA
		free(line_that_is_be_readen);
//4. Free na AUXILIAR
		free(auxiliar);
	}
	else
	{
		joined_and_returned = ft_calloc(ft_strlen(auxiliar), sizeof(char));
		ft_memcpy(joined_and_returned, auxiliar, ft_strlen(auxiliar));
		free(auxiliar);
	}
//5. Callocar na posição inicial da ESTÁTICA o comprimento da TERCEIRA string, gerada em 2
	line_that_is_be_readen = ft_calloc(ft_strlen(joined_and_returned), sizeof(char));
//6. Passar o conteúdo da TERCEIRA string para a variável ESTÁTICA
	while (*(joined_and_returned + index))
		{
			*(line_that_is_be_readen + index) = *(joined_and_returned + index);
			++index;
		}
//7. Free na TERCEIRA string
	free(joined_and_returned);
//8. Verifique se há uma quebra de linha na variável ESTÁTICA usando strchr
	if (ft_strchr(line_that_is_be_readen, '\n'))
	{
//9. Se houver quebra:
//	9.1. verifique em qual posição está a quebra de linha usando strlen aplicada na ESTÁTICA (certamente é possível obter isso a partir do resultado do item 4 ao invés do strlen)
		index = 0;
		while(*(line_that_is_be_readen + index) != '\n')
			++index;
//	9.2. use essa informação e a substr para criar uma substring RETORNADA com o conteúdo a ser retornado.
		joined_and_returned = ft_substr(line_that_is_be_readen, 0, (index + 1));
//	9.3. use novamente strlen para obter a quantidade de memória necessária para alocar o conteúdo restante, após a quebra de linha, numa variável AUXILIAR.
//	9.4. pegue a posição seguinte à quebra na ESTÁTICA e aloque todo o conteúdo a partir daí na variável AUXILIAR, usando memcpy por exemplo
		ft_memcpy(auxiliar, (line_that_is_be_readen + index + 1), (ft_strlen(line_that_is_be_readen + index + 1)));
//	9.6. free na ESTÁTICA
		if(ft_strncmp(line_that_is_be_readen, joined_and_returned, ft_strlen(line_that_is_be_readen)) == 0)
		{
			free(line_that_is_be_readen);
			return (joined_and_returned);
		}
//	9.7. calloque na ESTÁTICA a mesma quantidade de memória callocada no item 9.3 (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
		else
		{
			free(line_that_is_be_readen);
//	9.8. copie o conteúdo da string AUXILIAR, alocado em 9.4, para a ESTÁTICA (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
			line_that_is_be_readen = ft_calloc(ft_strlen(auxiliar), sizeof(char));
			ft_memcpy(line_that_is_be_readen, auxiliar, ft_strlen(auxiliar));
//	9.9. free na AUXILIAR (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra))
			free(auxiliar);
//	9.10. Retorne a string RETORNADA criada em 9.2.
			return (joined_and_returned);
		}
	}
//10. Se não houver quebra, mas eu chegar ao final do arquivo:
//	10.1. retorne a variável estática
	else if (end_file_identifier == 0)
		return(line_that_is_be_readen);
//11. Se não houver quebra, mas eu não chegar ao final do arquivo:
//	11.1. vá para o passo 0.
	else
		get_next_line(fd);
	return (NULL);
}

int	main (void)
{
	printf("O TEXTO É: \n%s", get_next_line(0));
	return (0);
}