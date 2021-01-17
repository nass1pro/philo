/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:26:13 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/17 15:48:19 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int				philo_eat(t_philo *philo)
{
	long int	start;

	philo->count_eat++;
	philo->is_eat = 1;
	philo->last_aet = get_time();
	philo->limit = philo->last_aet + philo->argg->time_to_die;
	if (out_message(TYPE_EAT, philo))
		return (1);
	start = get_time();
	while (get_time() - start <= philo->argg->time_to_eat)
		usleep(500);
	philo->is_eat = 0;
	philo->argg->cur_eat++;
	return (0);
}

int				philo_sleep_or_think(t_philo *philo, int type)
{
	long int	start;

	if (type == TYPE_SLEEP)
	{
		if (out_message(type, philo))
			return (1);
		start = get_time();
		while (get_time() - start <= philo->argg->time_to_sleep)
			usleep(500);
	}
	else if (out_message(type, philo))
		return (1);
	return (0);
}
