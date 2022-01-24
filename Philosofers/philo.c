/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:41:12 by vspinell          #+#    #+#             */
/*   Updated: 2021/09/13 17:15:44 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_table *table)
{
	pthread_mutex_destroy(table->fork);
	pthread_mutex_destroy(&table->print);
	if (table->fork)
		free(table->fork);
	if (table->philo)
		free(table->philo);
	if (table->info)
		free(table->info);
	if (table->th)
		free(table->th);
}

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;

	i = 1;
	if (argc != 5 && argc != 6)
		return (ft_error("Error: Invalid Arguments"));
	while (argv[i])
	{
		if (ft_check_str(argv[i++]) == 1)
			return (ft_error("Error: Invalid Arguments"));
	}
	i = 0;
	if (ft_init(&table, argv) == 1)
		return (1);
	while (i < table.philo_amount)
	{
		pthread_join(table.th[i], NULL);
		pthread_join(table.philo[i].cop, NULL);
		i++;
	}
	ft_free(&table);
	return (0);
}
