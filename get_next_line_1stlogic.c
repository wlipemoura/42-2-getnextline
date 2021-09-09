/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/09 15:34:24 by wfelipe-         ###   ########.fr       */
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

//1. Leia o FD o tanto que o buffer pedir.
//2. Armazene essa leitura numa string de retorno (se o arquivo acabar no tamanho dado pelo buffer, armazene apenas a quantidade necessária)
//3. Analize na string de retorno se há uma quebra de linha.
//4. Na primeira quebra de linha encontrada retorne o conteúdo presente desde o início da string até ela e salve a posição
//5. C
//3. Enquanto não estiver no fim do arquivo e não encontrar um '\n' siga lendo o arquivo e armazenando o conteúdo.
//4. Quando encontrar o primeiro 
//5. Se

//TROQUE OS NOMES DAS VARIÁVEIS DA SPLIT!!!!

#include <unistd.h>
#include <stdlib.h>

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


//0. Verificar a posição do último caractere na variável estática por meio da strlen (se não houver nada, considerar 0).
//1. Callocar buf bytes na variável estática a partir da posição após o último caractere para receber o conteúdo lido (se não houver nada, considerar a primeira posição)
//2. Ler BUF bytes no fd e alocar na variável estática
//3. Se a leitura não foi bem sucedida (read = 0), faça uma maracutaia que não sei o que é
//4. Se leu e deu certo, verifique se há uma quebra de linha nos caracteres alocados na estática usando strchr.
//5. Se houver quebra:
//	5.1. verifique em qual posição está a quebra de linha usando strlen aplicada na estática (certamente é possível obter isso a partir do resultado do item 4 ao invés do strlen)
//	5.2. use essa informação e a substr para criar uma substring com o conteúdo a ser retornado.
//	5.3. use novamente strlen para obter a quantidade de memória necessária para alocar o conteúdo restante, após a quebra de linha, numa variável auxiliar. Use o resultado do passo 4 para obter a posição.
//	5.4. pegue a posição seguinte à quebra na estática e aloque todo o conteúdo a partir daí na variável auxiliar, usando memcpy por exemplo
//	5.6. free na estática
//	5.7. calloque na estática a mesma quantidade de memória callocada no item 5.3 (pular esse passo se a estática for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
//	5.8. copie o conteúdo da string auxiliar para a estática (pular esse passo se a estática for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
//	5.9. free na auxiliar (pular esse passo se a estática for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra))
//	5.10. Retorne a string criada em 5.2.
//6. Se não houver quebra, mas eu chegar ao final do arquivo:
//	6.1. retorne a variável estática
//7. Se não houver quebra, mas eu não chegar ao final do arquivo:
//	7.1. vá para o passo 0.

char *get_next_line(int fd)
{
	static char	*line_that_is_be_readen;
	size_t		after_last_char_read_index;
	int			newline_address;
	size_t		newline_index;
	char 		*returned;
	char 		*auxiliar;
	int			end_file_identifier;
	int 		BUFFER_SIZE;
//0. Verificar a posição do último caractere na variável estática por meio da strlen (se não houver nada, considerar 0).
	(after_last_char_read_index = ft_strlen(line_that_is_be_readen));
//O BO TÁ AQUI:
//1. Callocar buf bytes na variável estática a partir da posição após o último caractere para receber o conteúdo lido (se não houver nada, considerar a primeira posição)
	(line_that_is_be_readen + after_last_char_read_index) = ft_calloc(BUFFER_SIZE, sizeof(char));
//2. Ler BUF bytes no fd e alocar na variável estática
	end_file_identifier = read(fd, (line_that_is_be_readen + after_last_char_read_index), BUFFER_SIZE);
//3. Se a leitura não foi bem sucedida (read = 0), faça uma maracutaia que não sei o que é
//4. Se leu e deu certo, verifique se há uma quebra de linha nos caracteres alocados na estática usando strchr.
	if (newline_address = ft_strchr(line_that_is_be_readen, '\n'))
//5.1. verifique em qual posição está a quebra de linha usando strlen aplicada na estática (certamente é possível obter isso a partir do resultado do item 4 ao invés do strlen)
	{
		while((line_that_is_be_readen + newline_index) != '\n')
			++newline_index;
//5.2. use essa informação e a substr para criar uma substring com o conteúdo a ser retornado.
		returned = ft_substr(line_that_is_be_readen, 0, (newline_index + 1));
//	5.3. use novamente strlen para obter a quantidade de memória necessária para alocar o conteúdo restante, após a quebra de linha, numa variável auxiliar. Use o resultado do passo 4 para obter a posição.
		auxiliar = ft_calloc((ft_strlen(newline_address + 1)), sizeof(char));
//	5.4. pegue a posição seguinte à quebra na estática e aloque todo o conteúdo a partir daí na variável auxiliar, usando memcpy por exemplo
		ft_memcpy(auxiliar, (newline_address + 1), (ft_strlen(newline_address + 1)));
//	5.6. free na estática
		//free(line_that_is_be_readen);
//	5.7. calloque na estática a mesma quantidade de memória callocada no item 5.3 (pular esse passo se a estática for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
		if(ft_strncmp(line_that_is_be_readen, returned, ft_strlen(line_that_is_be_readen)) = 0)
			free(line_that_is_be_readen);
		else
		{
			free(line_that_is_be_readen);
			line_that_is_be_readen = ft_calloc(ft_strlen(auxiliar), sizeof(char));
//	5.8. copie o conteúdo da string auxiliar para a estática (pular esse passo se a estática for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra)
			ft_memcpy(line_that_is_be_readen, auxiliar, ft_strlen(auxiliar));
//	5.9. free na auxiliar (pular esse passo se a estática for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra))
			free(auxiliar);
//	5.10. Retorne a string criada em 5.2.
			return (returned);
		}
	}
//6. Se não houver quebra, mas eu chegar ao final do arquivo:
//COMO É QUE EU SEI QUE CHEGUEI NO FINAL DO ARQUIVO, MANO?
//	6.1. retorne a variável estática
	else if (end_file_identifier = 0)
		return(line_that_is_be_readen);
//7. Se não houver quebra, mas eu não chegar ao final do arquivo:
//	7.1. vá para o passo 0.
	else
		get_next_line(fd);
	return (NULL);
}