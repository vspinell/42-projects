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
    
}               t_node;

typedef struct s_stacks
{
    t_node *head_a;
    t_node *head_b;
    int     len_a;
    int     len_b;

}               t_stacks;


int checker(t_stacks stacks);

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