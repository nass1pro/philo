/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:52 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 11:52:12 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			clear_all(t_targ ar)
{
	int		i;

	i = -1;
	sem_unlink("fork");
	sem_unlink("wt");
	while (i++ < ar.nb_ph)
		clean_fork(&ar.philo[i]);
	sem_post(ar.write_sc);
	sem_close(ar.write_sc);
	sem_close(ar.fork);
	free(ar.philo);
	return (0);
}
