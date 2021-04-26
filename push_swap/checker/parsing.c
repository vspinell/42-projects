#include "../checker.h"

t_data  *ft_stack(int count, char **arguments)
{
    t_data *head;
    int i;
    char **arg;
    int j;

    head = 0;
    i = 0;
    if (count == 1)
        return (0);
    while (--count)
    {
        j = 0;
        arg = ft_split(arguments[++i], ' ');
        while (arg[j])
        {
            if (!ft_check_str(arg[j]))
              {
                  write(1, "Error\n", 6);
                  exit(EXIT_FAILURE);
              }
            t_data *new;
            new = malloc(sizeof(t_data));
            if (!new)
            {
              write(1, "Error\n", 6);
              exit(EXIT_FAILURE);
            }
            new->num = ft_atoi(arg[j++]); //cambia con arg[j++]
            free(arg[j - 1]);
            new->next = 0;
            new->prev = 0;
            if (head == 0)
                head = new;
            else
            {
                t_data *last = head;
                while (last->next != 0)
                    last = last->next;
                new->prev = last;
                last->next = new;
            }
        }
            free(arg);
    }
    arg = 0;
    return (head);
}