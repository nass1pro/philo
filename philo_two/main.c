/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:56:13 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/23 14:07:59 by nahaddac         ###   ########.fr       */
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

static void		*monitor(void *philo_v)
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

void			*philo_life(void *philo)
{
	t_philo		*phi;
	pthread_t	tid;

	phi = (t_philo *)philo;
	phi->last_aet = phi->c_start;
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
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	if (arg->must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_eat, arg) != 0)
			return (1);
		pthread_detach(tid);
	}
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
