/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:09:24 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/23 09:31:33 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void			philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->count_eat++;
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;
	out_message(TYPE_EAT, philo);
	usleep(philo->argg->time_to_eat * 1000);
	philo->last_aet = get_time();
	philo->is_eat = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat);
}

void				philo_sleep_or_think(t_philo *philo, int type)
{
	long long	ti;

	if (type == TYPE_SLEEP)
	{
		if (philo->argg->time_to_eat > philo->argg->time_to_die ||
			philo->argg->time_to_sleep >= philo->argg->time_to_die)
		{
			ti = philo->argg->time_to_die - (get_time() - philo->last_aet);
			out_message(type, philo);
			usleep(ti * 1000);
			return ;
		}
		else
		{
			usleep(philo->argg->time_to_sleep * 1000);
			out_message(type, philo);
		}
	}
	else
		out_message(type, philo);
}
