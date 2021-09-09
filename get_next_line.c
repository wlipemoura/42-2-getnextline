/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/09 19:31:24 by wfelipe-         ###   ########.fr       */
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
//	9.4. pegue a posição seguinte à quebra na ESTÁTICA e aloque todo o conteúdo a partir daí na variável AUXILIAR, usando memmove por exemplo
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
#include "get_next_line.h"

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
		line_that_is_be_readen = NULL;
//4. Free na AUXILIAR
		free(auxiliar);
		auxiliar = NULL;
	}
	else
	{
		joined_and_returned = ft_calloc(ft_strlen(auxiliar), sizeof(char));
		ft_memmove(joined_and_returned, auxiliar, ft_strlen(auxiliar));
		free(auxiliar);
		auxiliar = NULL;
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
	joined_and_returned = NULL;
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
//	9.4. pegue a posição seguinte à quebra na ESTÁTICA e aloque todo o conteúdo a partir daí na variável AUXILIAR, usando memmove por exemplo
		auxiliar = ft_calloc(ft_strlen(line_that_is_be_readen + index), sizeof(char));
		ft_memmove(auxiliar, (line_that_is_be_readen + index + 1), (ft_strlen(line_that_is_be_readen + index + 1)));
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
			ft_memmove(line_that_is_be_readen, auxiliar, ft_strlen(auxiliar));
//	9.9. free na AUXILIAR (pular esse passo se a ESTÁTICA for igual à retornada - nesse caso o buffer acabou numa quebra, ou seja, não há sobra))
			free(auxiliar);
			auxiliar = NULL;
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
/*
int	main (void)
{
	int	fd;
	fd = open("file.txt",O_RDONLY);
	printf("O TEXTO É: \n%s", get_next_line(fd));
	return (0);
}
*/