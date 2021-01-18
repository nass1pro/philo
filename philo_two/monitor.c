/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:59 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/18 11:12:24 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

void			*monitor_eat(void *phi)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo*)phi;
	if (philo->argg->must_eat > 0)
		if (philo->count_eat == philo->argg->must_eat)
		{
			while (++i < philo->argg->nb_ph)
			{
				if (philo->argg->philo[i].count_eat >= philo->argg->must_eat)
					continue;
				else
					break ;
			}
			if (i == philo->argg->nb_ph)
			{
				end_prog_sem(philo, TYPE_OVER);
				sem_wait(philo->argg->somebody_dead_m);
				return ((void*)0);
			}
			return ((void*)0);
		}
	return ((void*)0);
}

void			*monitor(void *phi)
{
	t_philo			*philo;
	int				l;

	philo = (t_philo *)phi;
	l = 1;
	usleep(10000);
	while (l)
	{
		if (get_time() > philo->limit)
		{
			if (end_prog_sem(philo, TYPE_DIED))
				return ((void*)1);
			return ((void*)0);
		}
		usleep(1000);
	}
	return ((void*)0);
}

void			*monitor_flush(void *arg)
{
	t_targ			*ar;

	ar = (t_targ *)arg;
	while (1)
	{
		sem_wait(ar->write_sc);
		put_buff();
		sem_post(ar->write_sc);
		usleep(10000);
	}
	return ((void*)0);
}
