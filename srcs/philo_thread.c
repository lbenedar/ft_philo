/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 17:29:15 by lbenedar          #+#    #+#             */
/*   Updated: 2021/08/27 17:29:15 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	philo->right_fork->is_used = 1;
	out_change_state(philo, "has_taken_fork");
	philo->left_fork->is_used = 1;
	pthread_mutex_lock(&philo->left_fork->fork);
	out_change_state(philo, "has_taken_fork");
}

void	eat_with_forks(t_philo *philo)
{
	struct timeval	val;

	gettimeofday(&val, NULL);
	philo->time_of_last_eat = (val.tv_usec / 1000 + val.tv_sec * 1000) - philo->init_data->time_of_start;
	out_change_state(philo, "is_eating");
	usleep(philo->init_data->time_to_eat * 1000);
	++philo->have_eaten;
	philo->left_fork->is_used = 0;
	pthread_mutex_unlock(&philo->left_fork->fork);
	philo->right_fork->is_used = 0;
	pthread_mutex_unlock(&philo->right_fork->fork);
}

int	monitor(t_philo* philo)
{
	pthread_mutex_lock(&philo->init_data->waiter);
	if (!(philo->right_fork->is_used) && !(philo->left_fork->is_used))
	{
		take_forks(philo);
		pthread_mutex_unlock(&philo->init_data->waiter);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->init_data->waiter);
	return (0);
}

void	*philo_main(void *argv)
{
	t_philo *philo;

	philo = (t_philo*)argv;
	while (1)
	{
		if (monitor(philo))
		{
			eat_with_forks(philo);
			usleep(philo->init_data->time_to_sleep * 1000);
		}
		else
			usleep(50);
	}
	out_change_state(philo, "have eaten all food !!!");
	return (0);
}
