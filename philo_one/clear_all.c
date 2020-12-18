/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:11:51 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 11:46:49 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int				clear_all(t_targ ar)
{
	int			i;

	i = 0;
	pthread_mutex_destroy(&ar.write_sc);
	pthread_mutex_destroy(&ar.somebody_dead_m);
	while (i < ar.nb_ph)
	{
		pthread_mutex_destroy(&ar.fork[i]);
		pthread_mutex_destroy(&ar.philo[i].mutex);
		i++;
	}
	free(ar.philo);
	return (0);
}
