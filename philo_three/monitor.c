/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:29:12 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/14 16:45:59 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			*monitor_eat(void *arg_v)
{
	t_targ			*arg;
	int				i;

	arg = (t_targ*)arg_v;
	i = -1;
	while (++i < arg->nb_ph)
		sem_wait(arg->end);
	i = -1;
	while (++i < arg->nb_ph)
		sem_wait(arg->end);
	if (end_prog_sem(&arg->philo[0], TYPE_OVER))
		return ((void*)0);
	if (sem_post(arg->somebody_dead_m))
		return ((void*)0);
	return ((void*)0);
}

void				*monitor(void *philo_v)
{
	t_philo			*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if (sem_wait(philo->mutex))
			return ((void*)0);
		if (!philo->is_eat && get_time() > philo->limit)
		{
			if (end_prog_sem(philo, TYPE_DIED))
				return ((void*)0);
			if (sem_post(philo->argg->somebody_dead_m))
				return ((void*)0);
			return ((void*)0);
		}
		if (sem_post(philo->mutex))
			return ((void*)0);
		usleep(2000);
	}
	return ((void*)0);
}

int					start_m(t_targ *arg)
{
	pthread_t		tid;

	if (arg->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_eat, arg) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}
