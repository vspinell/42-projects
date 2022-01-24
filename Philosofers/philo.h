/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:41:26 by vspinell          #+#    #+#             */
/*   Updated: 2021/09/13 17:42:24 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_info
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	unsigned int	time_zero;
	int				isdead;
	int				check_visit;
	int				amount;
}				t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*action_print;
	t_info			*parse;
	pthread_t		cop;
	unsigned int	last_meal;
	int				counter;
}				t_philo;

typedef struct s_table
{
	int				philo_amount;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	t_info			*info;
	pthread_t		*th;
}				t_table;

int				ft_init(t_table *table, char **argv);
int				ft_atoi(char *str);
int				ft_error(char *str);
void			*ft_routine(void *arg);
unsigned int	ft_mtime(void);
unsigned int	ft_time(t_philo *philo, int p);
void			ft_usleep(int time, t_philo *philo);
int				ft_check_str(char *str);
int				ft_isdigit(int c);
void			*ft_routine2(void *arg);

#endif
