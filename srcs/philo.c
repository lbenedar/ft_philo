/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:11:46 by lbenedar          #+#    #+#             */
/*   Updated: 2021/08/14 18:11:46 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	out_error(int num_error)
{
	if (num_error == wrong_argv)
		printf("Wrong number of arguments\n");
	else if (num_error == mem_doesnt_alloc)
		printf("Couldn't allocate memory\n");
	else if (num_error == couldnt_create_thread)
		printf("Couldn't create thread\n");
}

void	out_philo_died(t_philo *philo, t_state state)
{
	struct timeval	val;
	long			time_passed;


	gettimeofday(&val, NULL);
	pthread_mutex_lock(&philo->init_data->display);
	philo->state = state;
	time_passed = (val.tv_usec / 1000 + val.tv_sec * 1000) - philo->init_data->time_of_start;
	printf("%ld %d died\n", time_passed, philo->nmb);
}

void	check_if_philo_died(t_philo *philo)
{
	int				i;
	struct timeval	vl;
	int				nmb_of_philo;
	int				j;

	nmb_of_philo = philo[0].init_data->nmb_of_philo;
	while (1)
	{
		i = 0;
		j = 0;
		usleep(50);
		while (i < nmb_of_philo)
		{
			if (philo[i].state == ate_all_food)
			{
				++i;
				++j;
				continue ;
			}
			gettimeofday(&vl, NULL);
			if ((vl.tv_usec / 1000 + vl.tv_sec * 1000) - philo[i].init_data->time_of_start -
				philo[i].time_of_last_eat >= philo[i].init_data->time_to_die)
			{
				//printf("current time %ld, time of last eat - %ld, time to die - %ld\n", (vl.tv_usec / 1000 + vl.tv_sec * 1000) - philo->init_data->time_of_start, philo[i].time_of_last_eat, philo[i].init_data->time_to_die);
				out_philo_died(philo + i, died);
				j = -1;
				break ;
			}
			++i;
		}
		if (j == nmb_of_philo)
		{
			usleep(50);
			break ;
		}
		else if (j == -1)
			break ;
	}
}

int	main(int argc, char **argv)
{
	int				err;
	t_philo_data	data;
	t_philo			*philo;

	if (argc > 4)
	{
		if (argc < 7)
		{
			err = setup_data(argv, &data, &philo);
			if (err)
				out_error(err);
			check_if_philo_died(philo);
		}
		else
			out_error(wrong_argv);
	}
	else
		out_error(wrong_argv);
	return (no_error);
}
