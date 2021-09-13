/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:15:29 by lbenedar          #+#    #+#             */
/*   Updated: 2021/08/27 19:15:29 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int 	cycle_setup_philos(t_philo_data *data, t_philo *philo, int i)
{
	struct timeval vl;

	gettimeofday(&vl, NULL);
	philo[i].nmb = i + 1;
	philo[i].have_eaten = 0;
	philo[i].state = is_thinking;
	philo[i].time_of_last_eat = 0;
	philo[i].left_fork = &data->forks[i];
	philo[i].right_fork = &data->forks[(i + 1) % data->nmb_of_philo];
	philo[i].init_data = data;
	if (pthread_create(&(philo[i].thread), NULL, 
						philo_main, (void*)(philo + i)))
		return (couldnt_create_thread);
	pthread_detach(philo[i].thread);
	return (no_error);
}

int     setup_philos(t_philo_data *data, t_philo **philo)
{
	int i;
	
	if (!(*philo = malloc(sizeof(t_philo) * data->nmb_of_philo)))
		return (mem_doesnt_alloc);
	i = 0;
	while (i < data->nmb_of_philo)
	{
		if (cycle_setup_philos(data, *philo, i))
			return (couldnt_create_thread);
		++i;
	}
	return (no_error);
}

int		setup_forks(t_philo_data *data)
{
	int				i;
	struct timeval	vl;

	if (gettimeofday(&vl, NULL))
		return (gettime_error);
	data->time_of_start = (vl.tv_usec / 1000 + vl.tv_sec * 1000);
	if (!(data->forks = malloc(sizeof(t_forks) * data->nmb_of_philo)))
		return (mem_doesnt_alloc);
	i = -1;
	while (++i < data->nmb_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i].fork), NULL))
			return (couldnt_init_mutex);
		data->forks[i].is_used = 0;
	}
	return (no_error);
}

int		setup_data(char **argv, t_philo_data *data, t_philo **philo)
{
	if ((data->nmb_of_philo = (int)ft_phil_atoi(argv[1])) < 1)
		return (wrong_argv);
	if ((data->time_to_die = ft_phil_atoi(argv[2])) < 1)
		return (wrong_argv);
	if ((data->time_to_eat = ft_phil_atoi(argv[3])) < 1)
		return (wrong_argv);
	if ((data->time_to_sleep = ft_phil_atoi(argv[4])) < 1)
		return (wrong_argv);
	if (argv[5])
	{
		if ((data->nmb_to_eat = (int)ft_phil_atoi(argv[5])) < 1)
			return (wrong_argv);
	}
	else
		data->nmb_to_eat = 0;
	data->used_forks = 0;
	if (pthread_mutex_init(&data->display, NULL))
		return (couldnt_init_mutex);
	if (pthread_mutex_init(&data->waiter, NULL))
		return (couldnt_init_mutex);
	if (setup_forks(data))
		return (couldnt_init_mutex);
	return (setup_philos(data, philo));
}
