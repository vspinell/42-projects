/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:21:42 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/03 12:21:50 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

int		ft_strlen(char *s);
char	*ft_realloc(char **line);
int		get_next_line(int fd, char **line);
char	*ft_reallocfin(char **line);
int		ft_newline(char *buff, char **line);
void	ft_buffupdate(char *buff, int j);
void	ft_bzero(void *s, size_t n);

#endif
