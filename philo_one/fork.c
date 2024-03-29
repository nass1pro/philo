/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:21:52 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/18 12:30:00 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void		take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->argg->fork[philo->l_fork]);
	pthread_mutex_lock(&philo->argg->fork[philo->r_fork]);
	out_message(TYPE_FORK, philo);
	out_message(TYPE_FORK, philo);
}

void		clean_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->argg->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->argg->fork[philo->r_fork]);
}
