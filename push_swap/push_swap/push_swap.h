# ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


//---per push swap--/
typedef struct s_node
{
    int             num;
    struct s_node *next;
    struct s_node *prev;
    int             pos;
    int             flags;
    
}               t_node;

typedef struct s_stacks
{
    t_node  *head_a;
    t_node  *head_b;
    int     count;
    //int     len_a;
    //int     len_b;

}               t_stacks;

//----push_swap---/

int push_swap(t_stacks vars);
t_node    *ft_subsequence(t_node *stack_a);
t_stacks  ft_sort_stacks(t_stacks gen);
int ft_max_flag(t_node *stack);
int ft_check_maxflag(t_node *stack, int max_flag);

//------utils3.c-----//

void	*ft_put_ones(size_t count);

//-------------//

char    **ft_split(char *s, char d);

t_node  *ft_stack(int count, char **arguments); // da dividere

//---utils.c---/ (full)

size_t     ft_strlen(char *s);
char	*ft_realloc(char *line, char c);
int		get_next_line(char **line);
int     ft_strncmp(char *s1, char *s2, size_t n);
void     ft_check_doubles(t_node *stack);
//----utils2.c---//

int     ft_check_str(char *str);
int     ft_atoi(const char *str);
int     ft_isdigit(int c);
int     ft_isspace(char c);

//---commands---// (full)

int ft_swap(t_node **stack);
int ft_rotate(t_node **head);
int ft_rev_rotate(t_node **head);
int ft_push(t_node **dst, t_node **src);
int ft_result(t_stacks *stacks);

# endif