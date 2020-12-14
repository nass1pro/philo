/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:09:24 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 12:05:01 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void			philo_eat(t_philo *philo)
{
	long long ti;

	ti = 0;
	philo->count_eat++;
	if (philo->argg->time_to_eat > philo->argg->time_to_die)
	{
		usleep((philo->argg->time_to_die) * 1000);
		out_message(TYPE_EAT, philo);
	}
	else
	{
		usleep(philo->argg->time_to_eat * 1000);
		philo->last_aet = get_time();
		out_message(TYPE_EAT, philo);
	}
}
