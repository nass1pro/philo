/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:59:48 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 12:15:25 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

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
