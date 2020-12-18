/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:18 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 07:54:20 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void		*philo_life(t_philo *phi)
{
	// phi->c_start = get_time();
	phi->last_aet = phi->c_start;
	while (get_time() - phi->last_aet < phi->argg->time_to_die ||
		phi->argg->must_eat_arg != 1)
	{
		take_fork(phi);
		if (phi->argg->must_eat_arg)
			break ;
		philo_eat(phi);
		if (phi->argg->must_eat_arg)
			break ;
		clean_fork(phi);
		if (phi->argg->must_eat_arg)
			break ;
		philo_sleep_or_think(phi, TYPE_SLEEP);
		if (phi->argg->must_eat_arg)
			break ;
		philo_sleep_or_think(phi, TYPE_THINK);
	}
	return (void *)phi;
}

int			philo_create(t_targ *arg)
{
	int		i;
	pid_t	*pid;

	i = 0;
	if (!(pid = malloc(sizeof(pid_t) * arg->nb_ph)))
		return (1);

	while (i < arg->nb_ph)
		arg->philo[i].c_start = get_time();
	i = 0;
	while (i < arg->nb_ph)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(0);
		if (pid[i] == 0)
			philo_life(&arg->philo[i]);
		usleep(40);
		i++;
	}
	i = -1;
	sem_wait(arg->philo_dead);
	sem_wait(arg->philo_dead);
	while (++i != arg->nb_ph)
		kill(pid[i], SIGUSR1);
	return (0);
}

/*
** 1: number_of_philosopher
** 2: time_to_die
** 3: time_to_eat
** 4: time_to_sleep
** 5: optionel[number_of_time_each_philosophers_must_eat]
*/

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
	usleep(20);
	clear_all(*arg);
	return (0);
}
