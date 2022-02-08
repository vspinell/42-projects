/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:44:51 by fulloa-s          #+#    #+#             */
/*   Updated: 2021/10/28 16:11:41 by fulloa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define KYEL "\x1B[33m"
# define KNRM  "\x1B[0m"
# define BBLU "\e[1;34m"

# define PERS_EXIT 32

extern int	g_info_exit;

typedef struct s_list
{
	int				i;
	char			*old_word;
	char			*new_word;
	struct s_list	*next;
}	t_list;

typedef struct s_info
{
	int		argc;
	char	**argv;
	char	**env_copy;

}	t_info;

typedef struct s_term
{
	int		fd_0;
	int		fd_1;
	int		n_cmd;
	char	*prompt;
	char	***cmd;
	t_info	info;
	t_list	*env;
	int		double_q;
	int		single_q;
	int		i;
	int		c_quote;
	int		q_skip;

}	t_term;

void			ft_unset(t_term *term, char **cmd);
void			ft_exec_pwd(char **cmd);
int				ft_check_builtin(char **cmd);
void			ft_builtinfunctions(t_term *term, char **cmd);
int				ft_names(t_term *term, int fd, int count);
int				ft_printbus(int fd);
void			ft_credits(t_term *term);
int				check_option(char *str);
void			ft_exec_echo(char **cmd);
void			ft_exec_echo2(char **cmd, int i);
void			ft_exec_echo3(char **cmd, int i);
void			ft_exec_cd(t_term *term, char **cmd);
void			ft_exec_cd2(t_term *term, char *oldpwd);
void			ft_exec_cd3(t_term *term, char **oldpwd);
void			ft_exec_cd4(t_term *term, char *pwd);
void			ft_exec_cd5(t_term *term, char **pwd, char **oldpwd);
void			ft_export(t_term *term, char **cmd);
void			ft_export2(t_term *term, char **cmd);
void			ft_export3(char **rebuild, t_list *tmp);
void			handler_dollar(t_term *term, char **cmd);
int				handler_dollar2(t_term *term, char **cmd, int c, int i);
int				handler_dollar3(t_term *term, char **cmd, int i, char **new);
char			*handler_dollar4(char **cmd, int i, int len_w, t_list *tmp);
int				handler_dollar5(char **cmd, int i, t_list *tmp, int len_w);
void			handler_dollar_f(t_term *term, char **cmd, int i, char **new);
int				handler_dollar_sing(t_term *term, char c);
int				handler_dollar_dou(t_term *term, char c);
void			handler_dollar_qm(t_term *term, char **cmd, int i);
int				ft_control_env(char **cmd);
int				handler_env(t_term *term, char **cmd_d, int pos);
int				handler_env2(t_term *term, char **old_tmp, char **new_tmp);
void			handler_env3(char **old_tmp, char **new_tmp, char *cmd, int i);
unsigned int	numbletter_orig(char const *s, char c);
unsigned int	ft_nbdigit(int n);
unsigned int	ft_sign(int n);
char			*fill(char *str, int n, unsigned int sign, unsigned int k);
char			*ft_itoa(int n);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(char *old, char *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
void			ft_matrix_add(char ***matrix, char *line_to_add);
void			ft_matrixcopy(char ***cp_matrix, char **matrix);
void			ft_matrixprint(char **matrix);
void			ft_matrixfree(char **matrix);
void			ft_matrix_remove_w2(t_term *term, char *rebuild, char del);
void			ft_matrix_remove_w(t_term *term, char *cmd,
					char del, int no_del);
int				ft_matrix_find_i_line(char **matrix, char *line_to_find);
void			ft_matrix_remove2(char ***matrix, char ***tmp, int rem_line);
void			ft_matrix_remove(char ***matrix, char *line_to_rem);
int				ft_matrixlen(char **cmd);
unsigned int	numbwords(char const *s, char c);
unsigned int	numbletter(char const *s, char c);
char			**mallocstring(char **str, char const *s,
					char c, unsigned int nb);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_isprint(int c);
int				ft_strchr(const char *s, int c);
int				ft_strchr_mod(const char *s, int c, int skip);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s1);
int				ft_countquotes(char *line);
int				ft_perror(char *str);
void			ft_putstr_fd(char *s, int fd);
int				ft_isspace(char *str);
char			*ft_realloc(char *path, char *cmd);
void			ft_usexecve(char *path, t_term *term, char **cmd);
int				ft_findpath(t_term *term, char *path);
int				ft_manage_env(t_term *term, int i);
void			ft_print_minishell(void);
void			ft_fillstruct(int argc, char **argv, char **env, t_term *term);
void			ft_info_list2(t_term *term, char **tmp, char **tmp1);
void			ft_info_list(t_term *term);
void			ft_init(t_term *term);
int				ft_checkquotes(char *str);
void			ft_parsing_init(t_term *term);
int				ft_errors(t_term *term);
void			ft_parsing_free(t_term *term);
void			ft_parsing(t_term *term);
void			ft_setfd(t_term *term, int i, int *fd);
void			ft_pipe_child(t_term *term, int path_line, int i);
void			ft_closefd(t_term *term, int *fd);
void			ft_pipe_check(t_term *term, int path_line, int i);
void			ft_pipeline(t_term *term, int path_line);
int				ft_str_nredir_count(int x, char **cmd, char *c);
char			**ft_sub_redir_imput(char ***cmd, int x, int check);
int				ft_redir_imput(t_term *term, char ***cmd);
size_t			ft_countredir(char *str);
void			ft_checkchar(t_term *term, char *str, int i);
int				ft_nredir_count(char *line, char *c);
int				ft_sub_checkredirline(char *str, int i, int count);
int				ft_checkredirline(t_term *term);
size_t			ft_countredir2(char *str, t_term *term);
int				ft_checkfile2(char ***cmd, int x, t_term *term);
int				ft_check_file(char ***cmd, int x, t_term *term);
int				ft_handle_remaninquote(t_term *term, char ***cmd,
					int check, int n);
int				ft_manageredir(t_term *term, char ***cmd);
int				ft_activateflag2(char c, int *d_q, int *s_q);
int				ft_check_specialcase(char ***cmd);
int				ft_isredir(char c);
int				ft_addstring_to_tmp(int flag, int y, char ***tmp, char *cmd);
char			**ft_special_realloc(char **cmd);
char			*ft_remove_char(char *str, int pos);
void			ft_activeflag(int *flag);
int				ft_quoteclean_routine(char **cmd, int *flag, int flag2, int y);
void			ft_quoteclean(char ***cmd);
void			handle_signals(int sig);
void			sigint_father(int sig);
void			sigint_child(int sig);
void			sigquit_child(int sig);
void			rl_replace_line(const char *str, int x);
void			ft_clearpath(char *str);
int				ft_notfound(char *str);

#endif
