/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:17:41 by lbenedar          #+#    #+#             */
/*   Updated: 2021/08/14 18:17:41 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef	struct	s_forks
{
	pthread_mutex_t	fork;
	char			is_used;
}				t_forks;

typedef struct	s_philo_data
{
    int				nmb_of_philo;
	int				nmb_to_eat;
	int				used_forks;
    long			time_to_eat;
    long			time_to_die;
    long			time_to_sleep;
	long			time_of_start;
	t_forks			*forks;
	pthread_mutex_t	display;
	pthread_mutex_t	waiter;
}				t_philo_data;

typedef struct	s_philo
{
    int				nmb;
    int				state;
	char			state_changed;
    int				have_eaten;
    long			time_of_last_eat;
	t_philo_data	*init_data;
	pthread_t		thread;
    t_forks			*left_fork;
	t_forks			*right_fork;
}				t_philo;

typedef enum    e_state
{
    has_taken_fork,
    is_eating,
    is_sleeping,
    is_thinking,
	ate_all_food,
    died
}               t_state;

typedef enum	e_error
{
	no_error,
	wrong_argv,
	mem_doesnt_alloc,
	couldnt_create_thread,
	couldnt_init_mutex,
	gettime_error
}				t_error;

int		setup_data(char **argv, t_philo_data *data, t_philo **philo);
long	ft_phil_atoi(char *str);
void    start_threads(char **argv);
void	*philo_main(void *argv);
void	out_change_state(t_philo *philo, char *output);