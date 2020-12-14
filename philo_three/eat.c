/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:38:27 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 10:14:20 by nahaddac         ###   ########.fr       */
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
		usleep(philo->argg->time_to_eat * 1000);
		philo->last_aet = get_time();
		out_message(TYPE_EAT, philo);
	}
}
