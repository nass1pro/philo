/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:56:13 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/08 06:52:04 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

void			*monitor_eat(void *phi)
{
	// t_targ			*arg;
	// int				i;
	t_philo 			*philo;

	philo = (t_philo*)phi;
	if (philo->argg->must_eat > 0)
		if (philo->count_eat == philo->argg->must_eat)
		{
			sem_wait(philo->mutex);
			if(philo->argg->cur_eat >= (philo->argg->must_eat * philo->argg->nb_ph))
			{
				if (end_prog_sem(philo, TYPE_OVER))
					return ((void*)0);
				if (sem_wait(philo->argg->somebody_dead_m))
					return ((void*)0);
			}
			else
				sem_wait(philo->mutex);
			return ((void*)0);
		}
	sem_post(philo->mutex);
	return ((void*)0);
}

static void			*monitor(void *arg)
{
	int 		l;
	t_targ 		*ar;
	int			i = 0;

	ar = (t_targ*)arg;
	l = 1;
	usleep(110);
	while (l)
	{
		while (i < ar->nb_ph)
		{
			i = 0;
			if (get_time() > ar->philo[i].limit + 2)
			{
				l = 0;
				if (end_prog_sem(&ar->philo[i], TYPE_DIED))
					return ((void*)1);
				return ((void*)0);
			}
			i++;
		}
	}
	return ((void*)0);
}


void				*philo_life(void *philo)
{
	t_philo		*phi;

	phi = (t_philo *)philo;
	phi->last_aet = get_time();
	phi->current = get_time() - phi->last_aet;
	phi->limit = phi->last_aet + phi->argg->time_to_die;
	sem_wait(phi->mutex);
	while (1)
	{
		sem_post(phi->mutex);
		monitor_eat(phi);
		if (take_fork(phi))
			return ((void*)0);
	}
	return ((void *)0);
}

int					philo_create(t_targ *arg)
{
	int			i;
	pthread_t	tid;

	i = 0;
	arg->start = get_time();
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	// if (arg->must_eat > 0)
	// {
	// 	if (pthread_create(&tid, NULL, &monitor_eat, arg) != 0)
	// 		return (1);
	// 	pthread_detach(tid);
	// }
	if (pthread_create(&tid, NULL, &monitor, arg) != 0)
		return (1);
	pthread_detach(tid);
	i = 0;
	while (i < arg->nb_ph)
	{
		if (pthread_create(&arg->philo[i].t_ph, NULL, &philo_life, &arg->philo[i]) != 0)
			return (1);
		pthread_detach(arg->philo[i].t_ph);
		i++;
	}
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
