/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 11:38:25 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/18 12:27:18 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void				*philo_life(void *philo)
{
	t_philo			*phi;
	pthread_t		tid;

	phi = (t_philo *)philo;
	pthread_mutex_lock(&phi->m_start);
	phi->last_aet = phi->argg->start;
	phi->limit = phi->last_aet + phi->argg->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, phi) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_fork(phi);
		philo_eat(phi);
		clean_fork(phi);
		philo_sleep_or_think(phi, TYPE_SLEEP);
		philo_sleep_or_think(phi, TYPE_THINK);
	}
	return (void *)0;
}

void				*monitor_flush(void *arg)
{
	t_targ			*ar;

	ar = (t_targ *)arg;
	usleep(10000);
	while (1)
	{
		pthread_mutex_lock(&ar->write_sc);
		put_buff();
		pthread_mutex_unlock(&ar->write_sc);
		usleep(10000);
	}
	return ((void*)0);
}

static void			start_philo(t_targ *arg)
{
	int				i;

	i = -1;
	while (++i < arg->nb_ph)
	{
		if (i % 2 == 0)
			pthread_mutex_unlock(&arg->philo[i].m_start);
	}
	usleep(1000);
	i = -1;
	while (++i < arg->nb_ph)
	{
		if (i % 2 == 1)
			pthread_mutex_unlock(&arg->philo[i].m_start);
	}
}

int					philo_create(t_targ *arg)
{
	int				i;
	pthread_t		tid;
	pthread_t		flush;

	i = 0;
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	if (arg->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_eat, arg))
			return (1);
		pthread_detach(tid);
	}
	i = -1;
	while (++i < arg->nb_ph)
	{
		pthread_create(&arg->philo[i].t_ph, NULL, &philo_life, &arg->philo[i]);
		pthread_detach(arg->philo[i].t_ph);
	}
	arg->start = get_time();
	start_philo(arg);
	if (pthread_create(&flush, NULL, &monitor_flush, arg) != 0)
		return (1);
	pthread_detach(flush);
	return (0);
}

int					main(int ac, char **argv)
{
	t_targ			*arg;
	int				i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (1);
	if (!(arg = malloc(sizeof(t_targ ) * 1)))
		return (ft_error(TYPE_ER_MAL));
	if (!(arg = init(arg, ac, argv)))
	{
		free(arg);
		return (ft_error(TYPE_ER_ARG));
	}
	init_philo(arg);
	philo_create(arg);
	pthread_mutex_lock(&arg->somebody_dead_m);
	pthread_mutex_unlock(&arg->somebody_dead_m);
	clear_all(arg);
	return (0);
}
