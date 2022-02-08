/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:24:58 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/14 09:30:56 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

void check_strlen()
{
	printf("\n================================\n");
	printf("========== FT_STRLEN ============\n");
	printf("================================\n\n");
	printf("\n");
	printf("IL MIO [%zu]\n", ft_strlen("ciao"));
	printf("\n");
	printf("IL SUO [%zu]\n", strlen("ciao"));
	printf("\n");
}

void check_write()
{ 
	char *str = "coglionazzo";

	printf("\n================================\n");
	printf("========== FT_WRITE ===========\n");
	printf("================================\n\n");
	printf("\n");
	printf("Mio con 5 [%zd]\n", ft_write(1, str, 5));
	printf("Suo con 5 [%zd]\n", write(1, str, 5));
	printf("\n");
	printf("Mio con 0 : %zd\n", ft_write(1, str,0));
	printf("Suo con 0 : %zd", write(1, str, 0));
	printf("\n");
	printf("Mio con fd invalido : %zd\n", ft_write(-7, str, 3));
	printf("Suo con fd invalido : %zd\n", write(-7, str, 3));
}
void check_strcpy()
{
	char s[] = "ciao";
	char d[] = "mond";

	printf("\n================================\n");
	printf("========== FT_STRCPY ============\n");
	printf("================================\n\n");
	printf("\n");
	printf("source before == [%s]\n", s);
	printf("destin before == [%s]\n", d);
	ft_strcpy(d, s);
	printf("destin after  == [%s]\n", d);
}

void check_strcmp()
{
	printf("\n================================\n");
	printf("========== FT_STRCMP ============\n");
	printf("================================\n\n");
	printf("\n");
	printf("\n");
	printf("\n");
	char	str1[] = "abcd", str2[] = "abCd", str3[] = "abcde";
	int	result;
	
	result = ft_strcmp(str1, str2);
	printf("ft_strcmp(str1, str2) = [%d]\n", result);
	result = strcmp(str1, str2);
	printf("strcmp(str1, str2) = [%d]\n", result);

	result = ft_strcmp(str1, str3);
	printf("\n\nft_strcmp(str1, str3) = [%d]\n", result);
	result = strcmp(str1, str3);
	printf("strcmp(str1, str3) = [%d]\n", result);
}

void check_read()
{
	char *buff;
	int i = 0;
	if (!(buff = malloc(2)))
	{
		puts("Something went wrong");
		exit(EXIT_FAILURE);
	}
	printf("\n#------  ft_read  ------#\n\n");
	printf("Now I'll guess what you wrote on the stdin, go on, i won't look\n");
	while ((ft_read(0, &(buff[i]), 1)) > 0)
	{
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			break ;
		}
		i++;
		buff = realloc(buff, i + 1);
	}
	printf("Let's see, i think you wrote\n""%s\n""was i right?\n", buff);
	free(buff);
}

void check_strdup()
{
	char *hello_world = "Hello world !";
	char *empty = "";
	char *save;
	char *save2;
	
	printf("\n================================\n");
	printf("========== FT_STRDUP ===========\n");
	printf("================================\n\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	save = strdup(hello_world);
	printf("%-20s: \"%s\"\n", "libc", save);
	free(save);
	save = NULL;
	save2 = ft_strdup(hello_world);
	printf("%-20s: \"%s\"\n", "libasm", save2);
	free(save2);
	save2 = NULL;
	printf("\n");
	printf("%-20s: \"%s\"\n", "char *", empty);
	save = strdup(empty);
	printf("%-20s: \"%s\"\n", "libc", save);
	free(save);
	save = NULL;
	save2 = ft_strdup(empty);
	printf("%-20s: \"%s\"\n", "libasm", save2);
	free(save2);
	save2 = NULL;
	printf("\n");
}

int main()
{
	check_strdup();
	check_strcmp();
	check_strlen();
	check_write();
	check_strcpy();
	check_read();
}
