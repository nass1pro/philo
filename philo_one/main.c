/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 11:38:25 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 04:36:51 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void		philo_sleep_or_think(t_philo *philo, int type)
{
	long long ti;

	if (type == TYPE_SLEEP)
	{
		if (philo->argg->time_to_eat > philo->argg->time_to_die ||
			philo->argg->time_to_sleep >= philo->argg->time_to_die)
		{
			ti = philo->argg->time_to_die - (get_time() - philo->last_aet);
			usleep(ti * 1000);
			out_message(type, philo);
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

void		ft_philo_dead(int type, t_philo *philo)
{
	char *time_stamp;
	char *id;

	if (!(time_stamp = malloc(sizeof(char) * 128)))
		return ;
	if (!(id = malloc(sizeof(char) * 5)))
		return ;
	message_tru(philo, id, time_stamp, type);
	free(time_stamp);
	free(id);
}

void		*philo_life(void *philo)
{
	t_philo *phi;

	phi = (t_philo *)philo;
	// phi->c_start = get_time();
	phi->last_aet = get_time();
	while (get_time() - phi->last_aet < phi->argg->time_to_die ||
		phi->argg->philo_dead != 1 || phi->argg->must_eat_arg != 1)
	{
		take_fork(phi);
		if (phi->argg->philo_dead == 1 || phi->argg->must_eat_arg)
			break ;
		philo_eat(phi);
		if (phi->argg->philo_dead == 1 || phi->argg->must_eat_arg)
			break ;
		clean_fork(phi);
		if (phi->argg->philo_dead == 1 || phi->argg->must_eat_arg)
			break ;
		philo_sleep_or_think(phi, TYPE_SLEEP);
		if (phi->argg->philo_dead == 1 || phi->argg->must_eat_arg)
			break ;
		philo_sleep_or_think(phi, TYPE_THINK);
	}
	pthread_mutex_unlock(&philo->argg->mutex)
	return (void *)phi;
}

/*
** 1: number_of_philosopher
** 2: time_to_die
** 3: time_to_eat
** 4: time_to_sleep
** 5: optionel[number_of_time_each_philosophers_must_eat]
*/

int			philo_create(t_targ *arg)
{
	int i;

	i = 0;
	while (i < arg->nb_ph)
	{
		pthread_create(&arg->philo[i].t_ph, NULL, &philo_life, &arg->philo[i]);
		arg->philo[i].c_start = get_time();
		//usleep(200);
		i++;
	}
	pthread_mutex_lock(&ar.mutex);
	while (arg->philo_dead != 1)
		;
	pthread_mutex_lock(&arg->write_sc);
	i = -1;
	while (i++ != arg->nb_ph)
		pthread_detach(arg->philo[i].t_ph);
	return (0);
}

int			main(int ac, char **argv)
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
	clear_all(*arg);
	return (0);
}
