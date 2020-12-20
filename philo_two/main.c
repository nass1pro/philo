/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:56:13 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 10:32:35 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

static void		*end_prog_sem(t_philo *philo, int type)
{
	if (out_message(type, philo))
		return ((void*)0);
	if (sem_post(philo->mutex))
		return ((void*)0);
	if (sem_post(philo->argg->somebody_dead_m))
		return ((void*)0);
	return ((void*)0);
}

static void		*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if (sem_wait(philo->mutex))
			return ((void*)0);
		if (philo->argg->must_eat != 0 && philo->count_eat ==
			philo->argg->must_eat)
			return (end_prog_sem(philo, TYPE_OVER));
		if (!philo->is_eat && get_time() > philo->limit)
			return (end_prog_sem(philo,TYPE_DIED));
		if (sem_post(philo->mutex))
			return ((void*)0);
		usleep(1000);
	}
	return ((void*)0);
}

void			*philo_life(void *philo)
{
	t_philo		*phi;
	pthread_t 	tid;
	phi = (t_philo *)philo;
	phi->last_aet = get_time();
	phi->limit = phi->last_aet + phi->argg->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		if (take_fork(phi))
			return ((void*)0);
		if (philo_eat(phi))
			return ((void*)0);
		if (clean_fork(phi))
			return ((void*)0);
		philo_sleep_or_think(phi, TYPE_SLEEP);
		philo_sleep_or_think(phi, TYPE_THINK);
	}
	return ((void *)0);
}

int				philo_create(t_targ *arg)
{
	int 		i;
	pthread_t 	tid;

	i = 0;
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	i = 0;
	while (i < arg->nb_ph)
	{
		if (pthread_create(&tid, NULL, &philo_life, &arg->philo[i]) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

int				main(int ac, char **argv)
{
	t_targ		*arg;
	int			i;

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
	if (philo_create(arg))
	{
		clear_all(*arg);
		return 1;
	}
	if (sem_wait(arg->somebody_dead_m))
		return 0;
	clear_all(*arg);
	return (0);
}
