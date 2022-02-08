/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:31:47 by vspinell          #+#    #+#             */
/*   Updated: 2021/10/27 17:39:16 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_term *term, char **cmd)
{
	if (!cmd[1])
		return ;
	if (!ft_strncmp(cmd[1], "PWD", ft_strlen("PWD")) \
	&& cmd[1][ft_strlen("PWD")] == '\0')
		return ;
	ft_matrix_remove_w(term, cmd[1], '=', 1);
}

void	ft_exec_pwd(char **cmd)
{
	char	*path;

	path = malloc(PATH_MAX);
	if (cmd[1])
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	if (getcwd(path, PATH_MAX) != NULL)
		printf("%s\n", path);
	free(path);
}

int	ft_check_builtin(char **cmd)
{
	if (!ft_strncmp("exit", cmd[0], 4) && cmd[0][4] == '\0')
		return (1);
	else if (!ft_strncmp("cd", cmd[0], 2) && cmd[0][2] == '\0')
		return (1);
	else if (!ft_strncmp("pwd", cmd[0], 3) && cmd[0][3] == '\0')
		return (1);
	else if (ft_strncmp("echo", cmd[0], 4) == 0)
		return (1);
	else if (!ft_strncmp("export", cmd[0], 6) && cmd[0][6] == '\0')
		return (1);
	else if (!ft_strncmp("unset", cmd[0], 5) && cmd[0][5] == '\0')
		return (1);
	else if (!ft_strncmp("env", cmd[0], 3) && cmd[0][3] == '\0')
		return (1);
	else if (!ft_strncmp("credits", cmd[0], 7) && cmd[0][7] == '\0')
		return (1);
	return (0);
}

void	ft_builtinfunctions(t_term *term, char **cmd)
{
	if (!ft_strncmp("exit", cmd[0], 4) && cmd[0][4] == '\0')
		exit (0);
	else if (ft_strncmp("echo", cmd[0], 4) == 0)
	{
		ft_exec_echo(cmd);
		g_info_exit = 0;
	}
	else if (!ft_strncmp("cd", cmd[0], 2) && cmd[0][2] == '\0')
		ft_exec_cd(term, cmd);
	else if (!ft_strncmp("pwd", cmd[0], 3) && cmd[0][3] == '\0')
		ft_exec_pwd(cmd);
	else if (!ft_strncmp("export", cmd[0], 6) && cmd[0][6] == '\0')
		ft_export(term, cmd);
	else if (!ft_strncmp("unset", cmd[0], 5) && cmd[0][5] == '\0')
		ft_unset(term, cmd);
	else if (!ft_strncmp("env", cmd[0], 3) && cmd[0][3] == '\0')
		ft_matrixprint(term->info.env_copy);
	else if (!ft_strncmp("credits", cmd[0], 7) && cmd[0][7] == '\0')
		ft_credits(term);
}
