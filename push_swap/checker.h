# ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//---per checker---//

typedef struct s_head
{
    struct s_data *head_a;
    struct s_data *head_b;

}               t_head;

typedef struct s_data
{
    int             num;
    struct s_data *next;
    struct s_data *prev;
    
}               t_data;

int checker(t_head stacks);

char    **ft_split(char *s, char d);

t_data  *ft_stack(int count, char **arguments); // da dividere

//---utils.c---/ (full)

size_t     ft_strlen(char *s);
char	*ft_realloc(char *line, char c);
int		get_next_line(char **line);
int     ft_strncmp(char *s1, char *s2, size_t n);
void     ft_check_doubles(t_data *stack);
//----utils2.c---//

int     ft_check_str(char *str);
int     ft_atoi(const char *str);
int     ft_isdigit(int c);
int     ft_isspace(char c);

//---commands---// (full)

int ft_swap(t_data **stack);
int ft_rotate(t_data **head);
int ft_rev_rotate(t_data **head);
int ft_push(t_data **dst, t_data **src);
int ft_result(t_head *stacks);

# endif