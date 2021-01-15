/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:59:48 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 15:26:21 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			clear_all(t_targ ar)
{
	sem_unlink("fork");
	sem_unlink("wt");
	sem_unlink("dead");
	sem_unlink("start");
	sem_unlink("grap");
	sem_unlink("mutex");
	free(ar.philo->argg);
	free(ar.philo);
	return (0);
}
