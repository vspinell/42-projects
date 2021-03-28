#include <stdio.h>
#include <stdlib.h>

int map_h = 5;
int spawn = 0;

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

int check_updown(char *first, char *last)
{
    int i = 0;
    while (first[i])
    {
        if (first[i] != '1')
            return(-1);
        i++;
    }
    i = 0;
    while (last[i])
    {
        if (last[i] != '1')
            return(-1);
        i++;
    }
    return (1);
}

int check_edges(char **map, int y)
{
    int current;
    int previous;
    int x;

    x = 0;
    current = ft_strlen(map[y]) -1;
    previous = ft_strlen (map[y - 1]) - 1;
    if (current < previous)
    {
       //puts (map[y]);
        x = current + 1;
        while (map[y-1][x])
        {
            if (map[y-1][x++] != '1')
            {
                printf("Map architecture problem [%c] row |%d| column |%d|\n", map[y - 1][x-1], y, x);
                return (-1);
            }
        }
    }
    else if (current > previous)
    {
        x = previous + 1;
        while (map[y][x])
        {
            if (map[y][x++] != '1')
            {
                printf("Map architecture problem [\"%c\"] row |%d| column |%d|\n", map[y][x-1], y + 1, x);
                return (-1);
            }
        }
    }
    return (1);
}

int check_line(char **map, int y)
{
    int x = 0;
    char c;
    if (check_edges(map, y) == -1)
        return (-1);
    while (map[y][x])
    {
        c = map[y][x];
        if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
            spawn++;
        if (c != '1' && c != 'W' && c != 'E' && c != 'S' && c != 'N' && c != '2'&& c != '0')
        {
            printf("Invalid character %c\n%s\n", c, map[y]);
            return (-1);
        }
        x++;
    }
    return (1);
}

int check_map(char **map)
{
    int i = 1;
    int len;
    if (check_updown(map[0], map[map_h]) == -1)
    {
        puts("Error in first or last row");
        return (-1);
    }
    while (i < map_h)
    {
        len = ft_strlen(map[i]) - 1;
        if (map[i][0] != '1' || map[i][len] != '1')
        {
            puts("Invalid borders");
            return (-1);
        }
        i++;
    }
    i = 1;
    while (i <= map_h)
    {
        if (check_line(map, i++) == -1)
          return (-1);
    }
    if (spawn != 1)
    {
        puts("Spawn is invalid");
        return (-1);
    }
   return (1);
}


int main(void)
{
    int i = 0;
    int j;
    char **map;
    map = malloc(7 * sizeof(char*));
    map[0] = "1111111111";
    map[1] = "10N001";
    map[2] = "100001";
    map[3] = "100001";
    map[4] = "111101";
    map[5] = "1111111";
    /*puts("here");
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 32)
               map[i][j] = '1';
            j++;
        }
        i++;
    }*/
    if (check_map(map) == -1)
        printf("Invalid Map\n");
    else
        printf("SUCCESS\n");
    i = 0;
    /*while(map[i])
        puts(map[i++]);*/
}
