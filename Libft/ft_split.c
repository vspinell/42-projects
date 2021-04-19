/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:51:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/01/23 16:51:41 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				puliscitutto(void **a, void *e)
{
	void		**tmp;

	tmp = a;
	while (*a <= e)
	{
		free(*a);
		a += 1 * sizeof(void*);
	}
	*tmp = NULL;
}

static char			**msplit(char const *s, char d, unsigned int *ui,
		unsigned int *uwc)
{
	unsigned int	word_count;
	unsigned int	i;
	unsigned int	y;

	if (!s)
		return (NULL);
	word_count = 0;
	i = 0;
	while (s[i])
	{
		y = 0;
		while (s[i + y] && s[i + y] != d)
			y += 1;
		if (y > 0)
		{
			word_count += 1;
			if (!s[i += y])
				break ;
		}
		i += 1;
	}
	word_count += 1;
	*ui = -1;
	*uwc = -1;
	return (malloc(word_count * sizeof(char*)));
}

char				**ft_split(char const *s, char d)
{
	char			**output;
	unsigned int	word_count;
	unsigned int	i;
	unsigned int	y;

	if (!s || !(output = msplit(s, d, &i, &word_count)))
		return (NULL);
	while ((y = 0) || s[++i])
	{
		while (s[i + y] && s[i + y] != d)
			y += 1;
		if (y > 0)
		{
			if (!(output[++word_count] = ft_substr(s, i, y)))
			{
				if (word_count > 0)
					puliscitutto((void**)output, &output[word_count - 1]);
				free(output);
				return (NULL);
			}
			if (!s[i += y])
				break ;
		}
	}
	return (output + (long)(output[++word_count] = NULL));
}
