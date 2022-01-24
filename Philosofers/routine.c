/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:10:22 by vspinell          #+#    #+#             */
/*   Updated: 2021/09/13 17:40:53 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_rfork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	pthread_mutex_lock(philo->action_print);
	if (philo->parse->isdead == 0)
		printf("%u\t%d\thas taken a fork\n", ft_time(philo, 0), philo->id + 1);
	pthread_mutex_unlock(philo->action_print);
}

void	ft_take_lfork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(philo->action_print);
	if (philo->parse->isdead == 0)
		printf("%u\t%d\thas taken a fork\n", ft_time(philo, 0), philo->id + 1);
	pthread_mutex_unlock(philo->action_print);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->action_print);
	if (philo->parse->isdead == 0)
		printf("%u\t%d\tis eating\n", ft_time(philo, 1), philo->id + 1);
	pthread_mutex_unlock(philo->action_print);
	ft_usleep(philo->parse->time_eat, philo);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	ft_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->action_print);
	if (philo->parse->isdead == 0)
		printf("%u\t%d\tis sleeping\n", ft_time(philo, 0), philo->id + 1);
	pthread_mutex_unlock(philo->action_print);
	ft_usleep(philo->parse->time_sleep, philo);
	pthread_mutex_lock(philo->action_print);
	if (philo->parse->isdead == 0)
		printf("%u\t%d\tis thinking\n", ft_time(philo, 0), philo->id + 1);
	pthread_mutex_unlock(philo->action_print);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	philo->last_meal = philo->parse->time_zero;
	pthread_create(&philo->cop, NULL, ft_routine2, philo);
	if (philo->id % 2 == 1)
		usleep(philo->parse->time_eat * 1000);
	while (philo->parse->isdead == 0)
	{
		ft_take_rfork(philo);
		if (philo->lfork == philo->rfork)
			break ;
		ft_take_lfork(philo);
		ft_eat(philo);
		if (philo->parse->must_eat != -1
			&& philo->counter >= philo->parse->must_eat)
			break ;
		ft_sleep_think(philo);
	}
	return (0);
}
