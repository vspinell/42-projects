/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:40:16 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/26 15:49:21 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cd2(t_term *term, char *oldpwd)
{
	t_list	*tmp;
	int		path_norme;

	tmp = term->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->old_word, "OLDPWD", ft_strlen("OLDPWD")) \
		&& tmp->old_word[ft_strlen("OLDPWD")] == '\0')
		{
			free(tmp->new_word);
			tmp->new_word = ft_strdup(oldpwd + 1);
			break ;
		}
		tmp = tmp->next;
	}
	path_norme = ft_findpath(term, "OLDPWD=");
	ft_matrix_remove(&term->info.env_copy, term->info.env_copy[path_norme]);
}

void	ft_exec_cd3(t_term *term, char **oldpwd)
{
	t_list	*tmp;
	char	*pwd;
	int		pos;

	pwd = ft_strjoin("OLDPWD", *oldpwd);
	pos = ft_findpath(term, "OLDPWD=");
	if (pos == -1)
	{
		tmp = ft_lstnew("OLDPWD", *oldpwd + 1);
		ft_lstadd_back(&term->env, tmp);
	}
	else
		ft_exec_cd2(term, *oldpwd);
	ft_matrix_add(&term->info.env_copy, pwd);
	free(*oldpwd);
	free(pwd);
}

void	ft_exec_cd4(t_term *term, char *pwd)
{
	t_list	*tmp;

	tmp = term->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->old_word, "PWD", ft_strlen("PWD")) \
		&& tmp->old_word[ft_strlen("PWD")] == '\0')
		{
			free(tmp->new_word);
			tmp->new_word = ft_strdup(pwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_exec_cd5(t_term *term, char **pwd, char **oldpwd)
{
	int	norme;

	*pwd = malloc(PATH_MAX);
	getcwd(*pwd, PATH_MAX);
	norme = ft_findpath(term, "PWD=");
	ft_matrix_remove(&term->info.env_copy, term->info.env_copy[norme]);
	*oldpwd = ft_strjoin("PWD=", *pwd);
	ft_matrix_add(&term->info.env_copy, *oldpwd);
}

void	ft_exec_cd(t_term *term, char **cmd)
{
	char	*pwd;
	char	*oldpwd;
	int		ret;
	int		pos;

	pos = ft_strchr(term->info.env_copy[ft_findpath(term, "PWD=")], '=');
	oldpwd = ft_strdup(term->info.env_copy[ft_findpath(term, "PWD=")] + pos);
	ret = chdir(cmd[1]);
	if (ret == -1)
	{
		free(oldpwd);
		if (!cmd[1])
			return ;
		printf("cd: %s: %s\n", cmd[1], strerror(errno));
		g_info_exit = 1;
	}
	else
	{
		ft_exec_cd3(term, &oldpwd);
		ft_exec_cd5(term, &pwd, &oldpwd);
		ft_exec_cd4(term, pwd);
		free(oldpwd);
		free(pwd);
	}
}
