/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   credits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:23:35 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/27 17:47:23 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_names(t_term *term, int fd, int count)
{
	char	*line;

	dup2(fd, 0);
	line = readline(GRN"");
	while (line && *line)
	{
		free(line);
		usleep(120000);
		if (count < 13)
			line = readline(GRN"");
		else if (count > 12 && count < 69)
			line = readline(BBLU"");
		else
			line = readline("");
		count++;
	}
	free(line);
	dup2(term->fd_0, 0);
	printf(KNRM);
	printf("\n\nTRY TO GUESS WHO MADE ALL OF THIS POSSIBLE\n");
	printf("\nType in the name below in lowercase\n");
	return (count);
}

int	ft_printbus(int fd)
{
	char	*line;

	dup2(fd, 0);
	line = readline("");
	while (line && *line)
	{
		free(line);
		usleep(120000);
		line = readline("");
		if (!ft_strncmp(line, "Ottima scelta...", 16)
			&& ft_strlen(line) == 16)
		{
			printf(KNRM);
			return (1);
		}
	}
	return (0);
}

void	ft_credits(t_term *term)
{
	char	*line;
	int		fd;
	int		tries;
	int		count;

	count = 0;
	tries = 4;
	fd = open("credits.txt", O_RDONLY);
	count = ft_names(term, fd, count);
	while (tries--)
	{
		line = readline("");
		if (!ft_strncmp(line, "mbus", 3) && ft_strlen(line) == 4)
		{
			if (ft_printbus(fd))
				return ;
		}
		else
			printf("\n%sWrong answer: %stry again:\n", RED, KNRM);
	}
	printf(KNRM);
	printf("\nWe are sorry but the names that you");
	printf(" typed in didn't contributed to this project\n");
}
