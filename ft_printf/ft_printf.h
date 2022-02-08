/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:27:42 by vspinell          #+#    #+#             */
/*   Updated: 2021/02/23 14:34:12 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_struct
{

	int		flag_z;
	int		flag_m;
	int		width;
	int		precision;
	char	type;
	int		counter;
	char	*s;
}				t_struct;

int				ft_printf(const char *format, ...);
int				ft_isdigit(int c);
void			ft_putchar(char c, t_struct *str);
void			ft_flags(const char **format, t_struct *str);
void			ft_width(const char **format, t_struct *str, va_list args);
void			ft_precision(const char **format, t_struct *str, va_list args);
void			ft_type(const char **format, t_struct *str);
int				ft_check(t_struct *str);
int				ft_strlen(char *s);
void			ft_putstr(char *s, t_struct *str);
void			ft_print(va_list args, t_struct *str);
int				ft_len(char *s, t_struct *str);
void			ft_putzero(int quantity, t_struct *str);
void			ft_putspace(int quantity, t_struct *str);
void			ft_precs(char *s, t_struct *str);
char			*ft_substr(char *string, int len);
char			*ft_strjoin(char *str1, char *str2);
char			*ft_fill_width(int count, t_struct *str);
void			ft_pad(int c, t_struct *str);
char			*ft_utoa(size_t n, int base, int len);
int				ft_intlen(size_t n, int base);
void			ft_treats(char *string, t_struct *str);
void			ft_treatd(int n, t_struct *str);
void			ft_isneg(int c, t_struct *str, int len);
void			ft_prec(int len, t_struct *str, int i);
void			ft_elseisneg(t_struct *str, int len);
void			uploads(t_struct *str);
void			ft_treatu(unsigned int n, t_struct *str, int base);
void			ft_toupper(t_struct *str);
int				ft_extrau(int n, t_struct *str, int len);
void			ft_treatp(size_t address, t_struct *str);
void			ft_treatc(char c, t_struct *str);
void			ft_piszero(t_struct *str);

#endif
