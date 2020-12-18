/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:21:52 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 08:53:31 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void		take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->argg->fork[philo->l_fork]);
	out_message(TYPE_FORK, philo);
	pthread_mutex_lock(&philo->argg->fork[philo->r_fork]);
	out_message(TYPE_FORK, philo);
}

void		clean_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->argg->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->argg->fork[philo->r_fork]);
}
