/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:20:15 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 11:12:29 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_philo *philo)
{
	sem_wait(philo->argg->fork);
	sem_wait(philo->argg->fork);
	if (philo->argg->must_eat_arg)
	{
		clean_fork(philo);
	}
	else
		out_message(TYPE_FORK, philo);
}

void		clean_fork(t_philo *philo)
{
	sem_post(philo->argg->fork);
	sem_post(philo->argg->fork);
}
