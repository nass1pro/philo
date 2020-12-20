/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 11:38:25 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 09:55:56 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void				philo_sleep_or_think(t_philo *philo, int type)
{
	long long	ti;

	if (type == TYPE_SLEEP)
	{
		if (philo->argg->time_to_eat > philo->argg->time_to_die ||
			philo->argg->time_to_sleep >= philo->argg->time_to_die)
		{
			ti = philo->argg->time_to_die - (get_time() - philo->last_aet);
			out_message(type, philo);
			usleep(ti * 1000);
			return ;
		}
		else
		{
			usleep(philo->argg->time_to_sleep * 1000);
			out_message(type, philo);
		}
	}
	else
		out_message(type, philo);
}

static void			*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->argg->must_eat != 0 && philo->count_eat ==
			philo->argg->must_eat)
		{
			out_message(TYPE_OVER, philo);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->argg->somebody_dead_m);
			return ((void*)0);
		}
		if (!philo->is_eat && get_time() > philo->limit)
		{
			out_message(TYPE_DIED, philo);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->argg->somebody_dead_m);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

void				*philo_life(void *philo)
{
	t_philo		*phi;
	pthread_t	tid;

	phi = (t_philo *)philo;
	phi->last_aet = get_time();
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

int					philo_create(t_targ *arg)
{
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	i = 0;
	while (i < arg->nb_ph)
	{
		pthread_create(&tid, NULL, &philo_life, &arg->philo[i]);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

int					main(int ac, char **argv)
{
	t_targ	*arg;
	int		i;

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
	clear_all(*arg);
	return (0);
}
