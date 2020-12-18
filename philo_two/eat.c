/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:26:13 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 14:44:29 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			philo_eat(t_philo *philo)
{
	long long ti;

	ti = 0;
	if (sem_wait(philo->mutex))
		return 1;
	philo->count_eat++;
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;

	if (out_message(TYPE_EAT, philo))
		return 1;
	usleep(philo->argg->time_to_eat * 1000);

	philo->last_aet = get_time();
	philo->is_eat = 0;
	if (sem_post(philo->mutex))
		return 1;
	return 0;
}
