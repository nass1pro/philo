/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:20:15 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 13:07:41 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		take_fork(t_philo *philo)
{
	sem_wait(philo->argg->sem_grap);
	sem_wait(philo->argg->fork);
	out_message(TYPE_FORK, philo);
	sem_wait(philo->argg->fork);
	out_message(TYPE_FORK, philo);
	sem_post(philo->argg->sem_grap);
	return (0);
}

int		clean_fork(t_philo *philo)
{
	sem_post(philo->argg->fork);
	sem_post(philo->argg->fork);
	return (0);
}
