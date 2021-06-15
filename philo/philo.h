/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:26:14 by jalease           #+#    #+#             */
/*   Updated: 2021/06/14 16:26:17 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_shared_data
{
	int						time_t_die;
	int						time_t_eat;
	int						time_t_sleep;
	int						nbr_of_meals;
	pthread_mutex_t			mutex_print;
}							t_shared_data;

typedef struct s_philosopher
{
	int						index;
	int						done;
	int						nbr_of_meals;
	long int				start_time;
	long int				last_meal;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	t_shared_data			*data;
}							t_philosopher;

typedef struct s_all
{
	pthread_mutex_t			*forks;
	t_philosopher			*philosophers;
	t_shared_data			shared_data;
	int						nbr_of_philosophers;
}							t_all;

void						start_threads(t_all *all);
void						start_monitor(t_all *all);
long int					get_time(long int start_time);
void						my_usleep(long int time);
void						print_msg(pthread_mutex_t *mutex_print,
								int id, long int time, char *msg);

int							ft_atoi(const char *str);
void						*ft_calloc(size_t count, size_t size);
void						ft_putnbr_fd(int n, int fd);
void						ft_putstr_fd(char *s, int fd);
size_t						ft_strlen(const char *s);
void						ft_putendl_fd(char *s, int fd);

#endif
