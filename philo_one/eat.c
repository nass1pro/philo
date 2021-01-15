/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:09:24 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 13:43:01 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void				philo_eat(t_philo *philo)
{
	long int	start;

	pthread_mutex_lock(&philo->mutex);
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;
	out_message(TYPE_EAT, philo);
	start = get_time();
	while (get_time() - start <= philo->argg->time_to_eat)
		usleep(500);
	philo->is_eat = 0;
	philo->count_eat++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat);
}

void				philo_sleep_or_think(t_philo *philo, int type)
{
	long int	start;

	if (type == TYPE_SLEEP)
	{
		start = get_time();
		while (get_time() - start <= philo->argg->time_to_sleep)
			usleep(500);
		out_message(type, philo);
	}
	else
		out_message(type, philo);
}
