/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:26:13 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/09 00:42:41 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int				philo_eat(t_philo *philo)
{
	long long	ti;

	ti = 0;
	philo->count_eat++;
	philo->argg->cur_eat++;
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;
	if (out_message(TYPE_EAT, philo))
		return (1);
	philo->current = get_time() - philo->last_aet;
	usleep(philo->argg->time_to_eat * 1000);
	// clean_fork(philo);
	philo->is_eat = 0;
	sem_post(philo->eat);
	return (0);
}

int				philo_sleep_or_think(t_philo *philo, int type)
{
	long long	ti;

	if (type == TYPE_SLEEP)
	{
		if (philo->argg->time_to_eat > philo->argg->time_to_die ||
			philo->argg->time_to_sleep >= philo->argg->time_to_die)
		{
			ti = philo->argg->time_to_die - (get_time() - philo->last_aet);
			if (out_message(type, philo))
				return (1);
			usleep(ti * 1000);
			return (1);
		}
		else
		{
			philo->last_aet = get_time();
			philo->current = get_time() - philo->last_aet;
			if (out_message(type, philo))
				return (1);
			usleep(philo->argg->time_to_sleep * 1000);
		}
	}
	else if (out_message(type, philo))
		return (1);
	return (0);
}
