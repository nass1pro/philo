/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 10:20:15 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 16:43:55 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		take_fork(t_philo *philo)
{
	sem_wait(philo->argg->fork);
	out_message(TYPE_FORK, philo);
	sem_wait(philo->argg->fork);
	out_message(TYPE_FORK, philo);
	if (philo->argg->must_eat_arg)
	{
		clean_fork(philo);
	}

}

void		clean_fork(t_philo *philo)
{
	sem_post(philo->argg->fork);
	sem_post(philo->argg->fork);
}
