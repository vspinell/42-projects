/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:47:41 by vspinell          #+#    #+#             */
/*   Updated: 2021/05/10 14:47:42 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_node
{
	int				num;
	struct s_node	*next;
	struct s_node	*prev;
	int				pos;
	int				pos_a;
	int				flags;
	int				star;
	int				movs_A;
	int				movs_B;
	int				tot_movs;
	int				dir;
	int				len_a;
	int				len_b;
}	t_node;

typedef struct s_stacks
{
	t_node	*head_a;
	t_node	*head_b;
}	t_stacks;

int			ft_pos_a(t_node *stack_a);
t_node		*ft_clean_stars(t_node *stack);
int			max_stackA(t_node *head);
void		ft_find_Apos(t_stacks *gen);
int			ft_movs_a(t_node node, int len_A);

t_node		*ft_best_move(t_node *stack);
t_node		*ft_findpos(t_node *stackA, int position);
int			ft_refreshpos(t_node *head, t_node *best);
t_node		*ft_min_stackA(t_node *head);
t_node		*ft_reorder_stack(t_node *head_a);

t_node		*ft_moves(t_node *stack);
t_node		*ft_moves2(t_node *stack, t_node *scroll);
t_stacks	ft_tot_movs(t_stacks gen);
t_stacks	light_push_swap(t_stacks gen, int len);

int			push_swap(t_stacks vars, int len);
int			ft_pos_a(t_node *stack_a);
t_node		*ft_init_flags(t_node *stack_a);
t_node		*ft_put_flags(t_node *stack_a);
int			ft_max_flag(t_node *stack);
t_stacks	ft_subsequence(t_stacks gen);
t_node		*ft_put_stars(t_node *head_a, int max_flag);
int			ft_min_numb(t_node *stack);

t_stacks	ft_sort_stacks(t_stacks gen);
int			ft_check_maxflag(t_node *stack, int max_flag);
int			ft_list_len(t_node **stack);
char		**ft_split(char *s, char d);

t_node		*ft_stack(int count, char **arguments);
t_node		*ft_newnode(char *arg);
t_node		*ft_add_back(t_node *nuovo, t_node *head);
void		ft_error(void);

size_t		ft_strlen(char *s);
char		*ft_realloc(char *line, char c);
int			get_next_line(char **line);
int			ft_strncmp(char *s1, char *s2, size_t n);
void		ft_check_doubles(t_node *stack);
int			ft_check_str(char *str);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_isspace(char c);
int			ft_swap(t_node **stack);
int			ft_rotate(t_node **head);
int			ft_rev_rotate(t_node **head);
int			ft_push(t_node **dst, t_node **src);
int			ft_result(t_node *stacks);

#endif
