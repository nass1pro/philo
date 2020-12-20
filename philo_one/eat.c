/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:09:24 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 09:24:32 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void			philo_eat(t_philo *philo)
{

	pthread_mutex_lock(&philo->mutex);
	philo->count_eat++;
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;
	out_message(TYPE_EAT, philo);
	usleep(philo->argg->time_to_eat * 1000);
	philo->last_aet = get_time();
	philo->is_eat = 0;
	pthread_mutex_unlock(&philo->mutex);
}
