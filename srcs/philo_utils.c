/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:14:55 by lbenedar          #+#    #+#             */
/*   Updated: 2021/08/27 19:14:55 by lbenedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long		ft_phil_atoi(char *str)
{
    int num;
	int i;

	num = 0;
	i = 0;
    while (str[i] > 47 && str[i] < 58)
		num = num * 10 + (str[i++] - 48);
	if (str[i])
		return (-1);
    return (num);
}