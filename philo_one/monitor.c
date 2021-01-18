/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:26:49 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/18 10:28:20 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void			*monitor_eat(void *arg_v)
{
	t_targ			*arg;
	int				i;
	int				total;

	arg = (t_targ*)arg_v;
	total = 0;
	while (total < arg->must_eat)
	{
		i = 0;
		while (i < arg->nb_ph)
			pthread_mutex_lock(&arg->philo[i++].eat);
		total++;
	}
	out_message(TYPE_OVER, &arg->philo[0]);
	pthread_mutex_unlock(&arg->somebody_dead_m);
	return ((void*)0);
}

void			*monitor(void *philo_v)
{
	t_philo			*philo;

	philo = (t_philo*)philo_v;
	usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eat && get_time() > philo->limit)
		{
			out_message(TYPE_DIED, philo);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->argg->somebody_dead_m);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(2000);
	}
}
