/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:56:13 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/18 11:10:47 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

void				*philo_life(void *philo)
{
	t_philo			*phi;
	pthread_t		tid;

	phi = (t_philo *)philo;
	pthread_create(&tid, NULL, &monitor, phi);
	pthread_detach(tid);
	sem_wait(phi->argg->sem_start);
	phi->argg->start = get_time();
	phi->last_aet = get_time();
	phi->current = get_time() - phi->last_aet;
	phi->limit = phi->last_aet + phi->argg->time_to_die;
	while (1)
	{
		take_fork(phi);
		philo_eat(phi);
		clean_fork(phi);
		monitor_eat(philo);
		philo_sleep_or_think(phi, TYPE_SLEEP);
		philo_sleep_or_think(phi, TYPE_THINK);
	}
	return ((void *)0);
}

int					philo_create(t_targ *arg)
{
	int			i;
	pthread_t	flush;

	i = 0;
	arg->start = get_time();
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	i = -1;
	while (++i < arg->nb_ph)
	{
		if (pthread_create(&arg->philo[i].t_ph, NULL,
			&philo_life, &arg->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(arg->philo[i].t_ph);
			return (1);
		}
	}
	if (pthread_create(&flush, NULL, &monitor_flush, arg) != 0)
		return (1);
	pthread_detach(flush);
	i = -1;
	while (++i < arg->nb_ph)
		sem_post(arg->sem_start);
	return (0);
}

int					main(int ac, char **argv)
{
	t_targ		*arg;
	int			i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (ft_error(TYPE_ER_ARG));
	if (!(arg = malloc(sizeof(t_targ ) * 1)))
		return (ft_error(TYPE_ER_MAL));
	if (!(arg = init(arg, ac, argv)))
	{
		free(arg);
		return (ft_error(TYPE_ER_ARG));
	}
	if (init_philo(arg))
	{
		free(arg);
		return (ft_error(TYPE_ER_MAL));
	}
	if (philo_create(arg))
		return (clear_all(*arg));
	if (sem_wait(arg->somebody_dead_m))
		return (0);
	clear_all(*arg);
	return (0);
}
