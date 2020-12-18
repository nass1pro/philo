/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:38:27 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 16:54:34 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			philo_eat(t_philo *philo)
{
	long long ti;

	ti = 0;
	philo->count_eat++;
	if (philo->argg->time_to_eat >= philo->argg->time_to_die)
	{
		usleep(philo->argg->time_to_die * 1000);
		out_message(TYPE_DIED, philo);
	}
	else
	{
		philo->last_aet = get_time();
		usleep(philo->argg->time_to_eat * 1000);
		out_message(TYPE_EAT, philo);
	}
}
