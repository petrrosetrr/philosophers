/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:30:12 by jalease           #+#    #+#             */
/*   Updated: 2021/06/15 19:30:14 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philosopher *philosopher)
{
	pthread_mutex_t	*mutex_print;
	long int		start_time;

	start_time = philosopher->start_time;
	mutex_print = &(philosopher->data->mutex_print);
	pthread_mutex_lock(philosopher->l_fork);
	print_msg(mutex_print, philosopher->index,
		get_time(start_time), "has taken left fork");
	pthread_mutex_lock(philosopher->r_fork);
	print_msg(mutex_print, philosopher->index,
		get_time(start_time), "has taken right fork");
	print_msg(mutex_print, philosopher->index,
		get_time(start_time), "is eating");
	philosopher->last_meal = get_time(0);
	my_usleep(philosopher->data->time_t_eat);
	pthread_mutex_unlock(philosopher->l_fork);
	pthread_mutex_unlock(philosopher->r_fork);
}

void	ph_sleep(t_philosopher *philosopher)
{
	pthread_mutex_t	*mutex_print;

	mutex_print = &(philosopher->data->mutex_print);
	print_msg(mutex_print, philosopher->index,
		get_time(philosopher->start_time), "is sleeping");
	my_usleep(philosopher->data->time_t_sleep);
}

void	ph_lifecycle(t_philosopher *philosopher)
{
	ph_eat(philosopher);
	ph_sleep(philosopher);
	print_msg(&(philosopher->data->mutex_print),
		philosopher->index, get_time(philosopher->start_time), "is thinking");
}

void	philosopher(t_philosopher *philosopher)
{
	philosopher->start_time = get_time(0);
	philosopher->last_meal = philosopher->start_time;
	while (1)
	{
		if (philosopher->nbr_of_meals == philosopher->data->nbr_of_meals)
			philosopher->done = 1;
		ph_lifecycle(philosopher);
		philosopher->nbr_of_meals++;
	}
}

void	start_threads(t_all *all)
{
	pthread_t	philosophers_t[2100];
	int			i;

	i = 0;
	while (i < all->nbr_of_philosophers)
	{
		pthread_create(&(philosophers_t[i]), NULL,
			(void *(*)(void *))philosopher, &(all->philosophers[i]));
		i += 2;
	}
	my_usleep(5);
	i = 1;
	while (i < all->nbr_of_philosophers)
	{
		pthread_create(&(philosophers_t[i]), NULL,
			(void *(*)(void *))philosopher, &(all->philosophers[i]));
		i += 2;
	}
	start_monitor(all);
	i = 0;
	while (i < all->nbr_of_philosophers)
	{
		pthread_join(philosophers_t[i], NULL);
		i++;
	}
}
