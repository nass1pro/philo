/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:18 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/18 10:56:33 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			*philo_life(void *philo)
{
	t_philo		*phi;
	pthread_t	tid;

	phi = (t_philo *)philo;
	sem_wait(phi->argg->sem_start);
	phi->last_aet = phi->c_start;
	phi->limit = phi->last_aet + phi->argg->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_fork(phi);
		philo_eat(phi);
		if (phi->count_eat == phi->must_eat)
			sem_post(phi->argg->end);
		clean_fork(phi);
		philo_sleep_or_think(phi, TYPE_SLEEP);
		philo_sleep_or_think(phi, TYPE_THINK);
	}
	return ((void *)0);
}

static pid_t	*start_f(t_targ *arg)
{
	pid_t		*pid;
	int			i;

	i = 0;
	if (!(pid = malloc(sizeof(pid_t) * arg->nb_ph)))
		return (NULL);
	while (i < arg->nb_ph)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(0);
		if (pid[i] == 0)
		{
			philo_life(&arg->philo[i]);
			exit(0);
		}
		i++;
	}
	return (pid);
}

int				philo_create(t_targ *arg)
{
	int			i;
	pid_t		*pid;

	i = 0;
	while (i < arg->nb_ph)
		arg->philo[i++].c_start = get_time();
	start_m(arg);
	pid = start_f(arg);
	i = arg->nb_ph;
	while (++i < arg->nb_ph)
		sem_post(arg->sem_start);
	sem_wait(arg->somebody_dead_m);
	sem_wait(arg->somebody_dead_m);
	i = arg->nb_ph;
	while (++i < arg->nb_ph)
		kill(pid[i], SIGKILL);
	free(pid);
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
	philo_create(arg);
	usleep(20);
	clear_all(*arg);
	return (0);
}
