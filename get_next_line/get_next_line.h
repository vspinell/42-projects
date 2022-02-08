/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:40:40 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/02 18:38:44 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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
