/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:10:35 by vspinell          #+#    #+#             */
/*   Updated: 2021/09/13 17:20:28 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_mtime(void)
{
	struct timeval	tv;
	unsigned int	tot_time;

	gettimeofday(&tv, NULL);
	tot_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (tot_time);
}

void	ft_mutex_init(t_table *table)
{
	int	i;
	int	sx;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->philo_amount);
	if (!table->fork)
		return ;
	pthread_mutex_init(&table->print, NULL);
	while (i < table->philo_amount)
	{
		sx = (1 + i) % table->philo_amount;
		table->philo[i].rfork = &table->fork[i];
		table->philo[i].lfork = &table->fork[sx];
		pthread_mutex_init(&table->fork[i], NULL);
		table->philo[i].action_print = &table->print;
		table->philo[i].parse = table->info;
		table->philo[i].counter = 0;
		i++;
	}
}

void	ft_philo_init(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philo_amount);
	if (!table->philo)
		return ;
	table->th = malloc(sizeof(pthread_t) * table->philo_amount);
	if (!table->th)
		return ;
	while (i < table->philo_amount)
	{
		table->philo[i].id = i;
		i++;
	}
}

void	ft_init_var(t_table *table, char **argv)
{
	table->philo_amount = ft_atoi(argv[1]);
	table->info->time_die = ft_atoi(argv[2]);
	table->info->time_eat = ft_atoi(argv[3]);
	table->info->time_sleep = ft_atoi(argv[4]);
	table->info->must_eat = 0;
	table->info->isdead = 0;
	table->info->check_visit = 0;
	table->info->amount = table->philo_amount;
	table->info->must_eat = -1;
}

int	ft_init(t_table *table, char **argv)
{
	int	i;

	i = -1;
	table->info = malloc(sizeof(t_info));
	if (!table->info)
		return (ft_error("Error: malloc failed"));
	ft_init_var(table, argv);
	if (table->philo_amount <= 0 || table->philo_amount > 200)
		return (ft_error("Error: Wrong number of philosofers"));
	if (argv[5])
		table->info->must_eat = ft_atoi(argv[5]);
	ft_philo_init(table);
	if (!table->philo)
		return (ft_error("Error: malloc failed"));
	ft_mutex_init(table);
	if (!table->fork)
		return (ft_error("Error: malloc failed"));
	table->info->time_zero = ft_mtime();
	while (++i < table->philo_amount)
		pthread_create(&table->th[i], NULL, ft_routine, &table->philo[i]);
	return (0);
}
