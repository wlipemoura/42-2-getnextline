/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfelipe- < wfelipe-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:19:22 by wfelipe-          #+#    #+#             */
/*   Updated: 2021/09/08 22:32:17 by wfelipe-         ###   ########.fr       */
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

#include <unisdt.h>
# include <stdlib.h>

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

pegue oomprimento lido (usando ft_strlen) que foi inserido na estática
//Calloque o comprimento numa string temporária, que servirá para permitir a limpeza da string estática
//
//Se for o último retorno, retorne a variável estática.
char *get_next_line(int fd)
{
	static char	*line_that_is_be_readen;
	char		*im_returning_bitch;
	char		*first_enter_index;
	char		*next_enter_index;
	char		*auxiliar;
	size_t		counter1;
	size_t		counter2;
	int			i_finished_the_file;

	counter1 = 0;
	counter2 = 0;
	line_that_is_be_readen = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	i_finished_the_file = read(fd, (line_that_is_be_readen + counter), BUFFER_SIZE);
	//Aqui imagine que tem um if para se der BO no read eu parar a função
	if (read worked well)//se leu alguma coisa, precisarei alocar no retorno (o que é feito no while). Aloco memória para preparar.
		im_returning_bitch = ft_calloc(ft_strlen(line_that_is_be_readen), sizeof(char));
	while(*(line_that_is_be_readen + counter1) && *(line_that_is_be_readen + counter1) != '\n')
	{
		*(im_returning_bitch + counter1) = *(line_that_is_be_readen + counter2);
		counter1++;
		counter2++;
	}
	first_enter_index = ft_strchr(line_that_is_be_readen + counter, '\n');//A: verifico se há algum \n lido
	//next_enter_index = ft_strchr(first_enter_index + 1, '\n');B: verifico se houveram dois \n lidos
	if (first_enter_index != NULL)//Se A for verdadeiro, preciso:
	//1. guardar o que tem depois do '\n' na variável estática
	//2. retornar o conteúdo até o '\n'
		auxiliar = ft_substr(first_enter_index + 1, ft_strlen(next_enter_index))
		free(line_that_is_be_readen);
		line_that_is_be_readen = ft_calloc(ft_strlen(auxiliar), sizof(char))
		ft_memcpy(line_that_is_be_readen, auxiliar);
		free(auxiliar);
		while (*(line_that_is_be_readen + counter1) !== '\n')

	if (first_enter_index = NULL)//Se A for falso, preciso continuar a leitura
	//last_enter_index = ft_strchr(next_enter_index + 1, '\n')
	
	if (i_finished_the_file = 0 || )
		return (im_returning_bitch);
		
		
		
		
		
	else
		get_next_line(fd);
}
