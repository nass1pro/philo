/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:20:15 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/23 14:03:02 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		take_fork(t_philo *philo)
{
	if (sem_wait(philo->argg->fork))
		return (1);
	if (out_message(TYPE_FORK, philo))
		return (1);
	if (sem_wait(philo->argg->fork))
		return (1);
	if (out_message(TYPE_FORK, philo))
		return (1);
	return (0);
}

int		clean_fork(t_philo *philo)
{
	if (sem_post(philo->argg->fork))
		return (1);
	if (sem_post(philo->argg->fork))
		return (1);
	return (0);
}
