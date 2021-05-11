/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:47:33 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/10 14:47:35 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_head
{
	struct s_data	*head_a;
	struct s_data	*head_b;

}	t_head;

typedef struct s_data
{
	int				num;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;

int		checker(t_head stacks);
int		ft_commandss(char *line, t_head *stacks, int ret);
int		ft_commands(char *line, t_head *stacks);
int		ft_result(t_head *stacks);
void	ft_KO(void);

char	**ft_split(char *s, char d);

t_data	*ft_stack(int count, char **arguments);
t_data	*ft_newnode(char *arg);
t_data	*ft_add_back(t_data *nuovo, t_data *head);
void	ft_error(void);

size_t	ft_strlen(char *s);
char	*ft_realloc(char *line, char c);
int		get_next_line(char **line);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_check_doubles(t_data *stack);
int		ft_check_str(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(char c);
int		ft_swap(t_data **stack);
int		ft_rotate(t_data **head);
int		ft_rev_rotate(t_data **head);
int		ft_push(t_data **dst, t_data **src);

#endif
