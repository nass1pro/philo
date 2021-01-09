/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:28:19 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/09 06:06:12 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			take_fork(t_philo *philo)
{
	sem_wait(philo->argg->fork);
	sem_wait(philo->argg->fork);
	monitor_eat(philo);
	if (philo_eat(philo))
		return 1;
	if (philo_sleep_or_think(philo, TYPE_SLEEP))
		return 1;
	if (philo_sleep_or_think(philo, TYPE_THINK))
		return 1;
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
