/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:26:32 by jalease           #+#    #+#             */
/*   Updated: 2021/06/14 16:26:34 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(long int start_time)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / (long)1000) - start_time);
}

void	my_usleep(long int time)
{
	long int	start_time;

	start_time = get_time(0);
	while (start_time + time > get_time(0))
	{
		usleep(100);
	}
}

void
	print_msg(pthread_mutex_t *mutex_print, int id, long int time, char *msg)
{
	pthread_mutex_lock(mutex_print);
	ft_putnbr_fd((int)time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(id, 1);
	write(1, " ", 1);
	ft_putendl_fd(msg, 1);
	pthread_mutex_unlock(mutex_print);
}
