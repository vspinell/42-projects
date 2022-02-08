/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:23:31 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/14 09:30:49 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBASM_H
# define LIBASM_H

# include	<string.h>
# include	<stdio.h>
# include	<unistd.h>
# include   <stdlib.h>
# include   <errno.h>

size_t		ft_strlen(const char *s);
ssize_t     ft_write(int fildes, const void *buf, size_t nbyte);
char        *ft_strcpy(char *dst, const char *src);
int         ft_strcmp(const char *s1, const char *s2);
char        *ft_strdup(const char *s1);
ssize_t     ft_read(int fildes, void *buf, size_t nbyte);

#endif
