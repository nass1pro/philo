/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:29:12 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/23 14:33:38 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			*monitor_eat(void *arg_v)
{
	t_targ 			*arg;
	int				i;

	arg = (t_targ*)arg_v;
	while (arg->cur_eat < arg->must_eat)
	{
		i = 0;
		while (i < arg->nb_ph)
			if (sem_wait(arg->philo[i++].eat))
				return ((void*)0);
		arg->cur_eat++;
	}
	if (end_prog_sem(&arg->philo[0], TYPE_OVER))
		return ((void*)0);
	if (sem_wait(arg->somebody_dead_m))
		return ((void*)0);
	return ((void*)0);
}

void		*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if (sem_wait(philo->mutex))
			return ((void*)0);
		if (!philo->is_eat && get_time() > philo->limit)
		{
			if (end_prog_sem(philo, TYPE_DIED))
				return ((void*)0);
			return ((void*)0);
		}
		if (sem_post(philo->mutex))
			return ((void*)0);
		usleep(10);
	}
	return ((void*)0);
}

int         start_m(t_targ *arg)
{
    pthread_t	tid;

    if (arg->must_eat > 0)
    {
        if (pthread_create(&tid, NULL, &monitor_eat, arg) != 0)
            return (1);
        pthread_detach(tid);
    }
    return (0);
}
