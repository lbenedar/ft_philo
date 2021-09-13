/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 20:14:20 by lbenedar          #+#    #+#             */
/*   Updated: 2021/08/27 20:14:20 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	out_change_state(t_philo *philo, char *output)
{
	struct timeval	val;
	long			time_passed;

	gettimeofday(&val, NULL);
	time_passed = (val.tv_usec / 1000 + val.tv_sec * 1000) - philo->init_data->time_of_start;
	pthread_mutex_lock(&philo->init_data->display);
	printf("%ld %d %s\n", time_passed, philo->nmb, output);
	//if (philo->state == has_taken_fork)
	//	printf("%ld %d has taken a fork\n", time_passed, philo->nmb);
	//else if (philo->state == is_eating)
	//	printf("%ld %d is eating\n", time_passed, philo->nmb);
	//else if (philo->state == is_sleeping)
	//	printf("%ld %d is sleeping\n", time_passed, philo->nmb);
	//else if (philo->state == is_thinking)
	//	printf("%ld %d is thinking\n", time_passed, philo->nmb);
	//else if (philo->state == ate_all_food)
	//	printf("%ld %d have eaten all food !!!\n", time_passed, philo->nmb);
	pthread_mutex_unlock(&philo->init_data->display);
}