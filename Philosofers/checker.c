/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:41:27 by vspinell          #+#    #+#             */
/*   Updated: 2021/09/13 17:47:11 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_must_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->action_print);
	philo->parse->check_visit++;
	if (philo->parse->check_visit == philo->parse->amount)
	{
		philo->parse->isdead = 1;
		printf("%u\tmust eat count reached\n", ft_time(philo, 0));
	}
}

void	*ft_routine2(void *arg)
{
	t_philo			*philo;
	unsigned int	die;

	philo = (t_philo *)arg;
	die = philo->parse->time_die;
	while (philo->parse->isdead == 0)
	{
		if (ft_mtime() - philo->last_meal > die)
		{
			pthread_mutex_lock(philo->action_print);
			philo->parse->isdead++;
			if (philo->parse->isdead == 1)
				printf("%u\t%d\tdied\n", ft_time(philo, 0), philo->id + 1);
			pthread_mutex_unlock(philo->action_print);
		}
		else if (philo->parse->must_eat != -1
			&& philo->counter == philo->parse->must_eat)
		{
			ft_must_eat(philo);
			pthread_mutex_unlock(philo->action_print);
			break ;
		}
		ft_usleep(5, philo);
	}
	return (0);
}

unsigned int	ft_time(t_philo *philo, int p)
{
	unsigned int	time;

	time = ft_mtime();
	if (p == 1)
	{
		philo->last_meal = time;
		philo->counter++;
	}
	return (time - philo->parse->time_zero);
}

void	ft_usleep(int time, t_philo *philo)
{
	unsigned int	end;

	end = ft_mtime() + time;
	while (ft_mtime() < end && (philo->parse->isdead == 0))
		usleep(time);
}
