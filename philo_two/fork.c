/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:28:19 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/09 18:12:56 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			take_fork(t_philo *philo)
{
	sem_wait(philo->argg->sem_grap);
	sem_wait(philo->argg->fork);
	out_message(TYPE_FORK, philo);
	sem_wait(philo->argg->fork);
	out_message(TYPE_FORK, philo);
	sem_post(philo->argg->sem_grap);
	monitor_eat(philo);

	return (0);
}

int			clean_fork(t_philo *philo)
{
	if (sem_post(philo->argg->fork))
		return (1);
	if (sem_post(philo->argg->fork))
		return (1);
	return (0);
}

void		*end_prog_sem(t_philo *philo, int type)
{
	if (out_message(type, philo))
		return ((void*)0);
	if (sem_post(philo->argg->somebody_dead_m))
		return ((void*)0);
	return ((void*)0);
}
