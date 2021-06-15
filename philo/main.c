/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:27:33 by jalease           #+#    #+#             */
/*   Updated: 2021/06/14 16:27:36 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_all *all, int ac, char **av)
{
	if (ac >=5 && ac <=6)
	{
		all->nbr_of_philosophers = ft_atoi(av[1]);
		all->shared_data.time_t_die = ft_atoi(av[2]);
		all->shared_data.time_t_eat = ft_atoi(av[3]);
		all->shared_data.time_t_sleep = ft_atoi(av[4]);
		all->shared_data.nbr_of_meals = -1;
		if (ac == 6)
			all->shared_data.nbr_of_meals = ft_atoi(av[5]);
		all->philosophers = ft_calloc(all->nbr_of_philosophers,
				sizeof (t_philosopher));
		all->forks = ft_calloc(all->nbr_of_philosophers,
				sizeof (pthread_mutex_t));
		return (1);
	}
	return (0);
}

void	init_mutex(pthread_mutex_t *mutex, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_init(&(mutex[i]), NULL);
		i++;
	}
}

void	init_philosophers(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nbr_of_philosophers)
	{
		all->philosophers[i].index = i;
		all->philosophers[i].nbr_of_meals = 0;
		all->philosophers[i].done = 0;
		all->philosophers[i].data = &(all->shared_data);
		all->philosophers[i].r_fork = &(all->forks[i]);
		if (i != all->nbr_of_philosophers - 1)
			all->philosophers[i].l_fork = &(all->forks[i + 1]);
		else
			all->philosophers[i].l_fork = &(all->forks[0]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_all	all;

	if (init_data(&all, ac, av))
	{
		init_mutex(all.forks, all.nbr_of_philosophers);
		init_mutex(&(all.shared_data.mutex_print), 1);
		init_philosophers(&all);
		start_threads(&all);
		start_monitor(&all);
		return (0);
	}
	else
		return (1);
}
