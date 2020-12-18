/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:09:24 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 07:07:09 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void			philo_eat(t_philo *philo)
{
	long long ti;

	ti = 0;
	philo->count_eat++;
	if (philo->argg->time_to_eat >= philo->argg->time_to_die)
	{
		usleep((philo->argg->time_to_die) * 1000);
		out_message(TYPE_DIED, philo);
	}
	else
	{
		usleep(philo->argg->time_to_eat * 1000);
		philo->last_aet = get_time();
		out_message(TYPE_EAT, philo);
	}
}
