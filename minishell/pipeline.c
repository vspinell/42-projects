/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:50:32 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/29 20:19:04 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setfd(t_term *term, int i, int *fd)
{
	if (i >= 0 && i < term->n_cmd - 1 && term->n_cmd != 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	else if (i == term->n_cmd - 1 || term->n_cmd == 1)
	{
		close(fd[1]);
		close(fd[0]);
		dup2(term->fd_1, 1);
	}
}

void	ft_pipe_child(t_term *term, int path_line, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	handle_signals(2);
	if (pid == 0)
		ft_usexecve(term->info.env_copy[path_line], term, term->cmd[i]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		g_info_exit = 128 + WTERMSIG(status);
	else
		g_info_exit = WEXITSTATUS(status);
	if (WEXITSTATUS(status) == 127)
	{
		dup2(term->fd_1, 1);
		printf("%s: command not found\n", term->cmd[i][0]);
	}
}

void	ft_closefd(t_term *term, int *fd)
{
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(term->fd_1, 1);
	close(term->i);
}

void	ft_pipe_check(t_term *term, int path_line, int i)
{
	if (ft_manageredir(term, &term->cmd[i]) != -1)
	{
		if (ft_check_builtin(term->cmd[i]))
			ft_builtinfunctions(term, term->cmd[i]);
		else
			ft_pipe_child(term, path_line, i);
	}
}

void	ft_pipeline(t_term *term, int path_line)
{
	int			i;
	int			fd[2];
	int			y;
	struct stat	buff;

	i = 0;
	while (term->cmd[i])
	{
		pipe(fd);
		if (ft_manage_env(term, i) != 1 && ft_manage_env(term, i) != 3)
		{
			ft_setfd(term, i, fd);
			y = 0;
			while (term->cmd[i] && term->cmd[i][y])
				handler_dollar(term, &term->cmd[i][y++]);
			term->cmd[i] = ft_special_realloc(term->cmd[i]);
			ft_pipe_check(term, path_line, i);
			if (!stat("temp", &buff) && i == term->n_cmd - 1)
				unlink("temp");
			ft_closefd(term, fd);
		}
		i++;
	}
}
