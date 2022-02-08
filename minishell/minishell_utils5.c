/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:51:43 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/28 13:52:45 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *path, char *cmd)
{
	size_t		i;
	int			j;
	size_t		len;
	char		*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(path) + ft_strlen(cmd) + 1;
	tmp = malloc(sizeof(char) * len + 2);
	while (i < ft_strlen(path))
	{
		tmp[i] = path[i];
		i++;
	}
	tmp[i++] = '/';
	while (i < len)
	{
		tmp[i] = cmd[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	ft_usexecve(char *path, t_term *term, char **cmd)
{
	char	**path_matrix;
	int		i;
	char	*tmp;

	i = 0;
	execve(cmd[0], cmd, term->info.env_copy);
	path_matrix = ft_split(path + 5, ':');
	while (path_matrix[i])
	{
		tmp = ft_realloc(path_matrix[i], cmd[0]);
		if (execve(tmp, cmd, term->info.env_copy) == -1)
			i++;
		else
		{
			free(tmp);
			i = -1;
			break ;
		}
		free(tmp);
	}
	ft_matrixfree(path_matrix);
	exit(127);
}

int	ft_findpath(t_term *term, char *path)
{
	int	i;

	i = 0;
	while (term->info.env_copy[i])
	{
		if ((ft_strncmp(path, term->info.env_copy[i], ft_strlen(path)) != 0))
			i++;
		else
			return (i);
	}
	if (!ft_strncmp("PATH=", path, ft_strlen("PATH=")) && ft_strlen(path) == 5)
	{
		printf("\033[0;31mERROR, no PATH ENV\033[0;37m\n");
		exit(1);
	}
	return (-1);
}

int	ft_manage_env(t_term *term, int i)
{
	int		y;
	int		ret;
	int		x;

	x = -1;
	y = 0;
	ret = 0;
	while (term->cmd[i][y])
	{	
		ret = handler_env(term, &term->cmd[i][y], i);
		if (ret == 0 || ret == 2 || ret == 3)
			break ;
		y++;
	}
	if (ret == 2)
	{
		y = ft_control_env(term->cmd[i]);
		while (++x < y)
			ft_matrix_remove(&term->cmd[i], term->cmd[i][0]);
	}
	return (ret);
}

void	ft_print_minishell(void)
{
	printf("\n%s   ███╗   ███╗██╗███╗   ██╗██╗███████╗", KYEL);
	printf("%s██╗  ██╗███████╗██╗     ██╗     \n", KYEL);
	printf("%s   ████╗ ████║██║████╗  ██║██║██╔════╝", KYEL);
	printf("%s██║  ██║██╔════╝██║     ██║     \n", KYEL);
	printf("%s   ██╔████╔██║██║██╔██╗ ██║██║███████╗", KYEL);
	printf("%s███████║█████╗  ██║     ██║     \n", KYEL);
	printf("%s   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║", KYEL);
	printf("%s██╔══██║██╔══╝  ██║     ██║     \n", KYEL);
	printf("%s   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║", KYEL);
	printf("%s██║  ██║███████╗███████╗███████╗\n", KYEL);
	printf("%s   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝", KYEL);
	printf("%s╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n", KYEL);
	printf("%s                                  ", KYEL);
	printf("%s                                    \n", KYEL);
	printf(KNRM);
}
