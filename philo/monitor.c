/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:16:59 by jalease           #+#    #+#             */
/*   Updated: 2021/06/15 19:17:01 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	health_check(t_all *all, int i)
{
	t_philosopher	*philosophers;

	philosophers = all->philosophers;
	if (get_time(philosophers[i].last_meal) >= (long int)
		all->shared_data.time_t_die)
	{
		pthread_mutex_lock(&(all->shared_data.mutex_print));
		ft_putnbr_fd((int)get_time(philosophers[i].start_time), 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philosophers[i].index, 1);
		ft_putendl_fd(" died", 1);
		return (0);
	}
	return (1);
}

void	monitor(t_all *all)
{
	int				done;
	int				i;
	t_philosopher	*philosophers;

	philosophers = all->philosophers;
	while (1)
	{
		i = 0;
		done = 1;
		while (i < all->nbr_of_philosophers)
		{
			if (!(philosophers[i].done))
				done = 0;
			if (!health_check(all, i))
				return ;
			i++;
		}
		if (done)
		{
			pthread_mutex_lock(&(all->shared_data.mutex_print));
			return ;
		}
	}
}

void	start_monitor(t_all *all)
{
	pthread_t	monitor_t;

	pthread_create(&monitor_t, NULL, (void *(*)(void *))monitor, all);
	pthread_join(monitor_t, NULL);
}
