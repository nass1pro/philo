/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:38:27 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 12:52:49 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				philo_eat(t_philo *philo)
{
	long int	start;

	if (sem_wait(philo->mutex))
		return (1);
	philo->count_eat++;
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;
	if (out_message(TYPE_EAT, philo))
		return (1);
	start = get_time();
	while (get_time() - start <= philo->argg->time_to_eat)
		usleep(500);
	philo->last_aet = get_time();
	philo->is_eat = 0;
	if (sem_post(philo->mutex))
		return (1);
	if (sem_post(philo->eat))
		return (1);
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
			usleep(philo->argg->time_to_sleep * 1000);
			if (out_message(type, philo))
				return (1);
		}
	}
	else if (out_message(type, philo))
		return (1);
	return (0);
}
