/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 08:00:59 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 12:04:41 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int			ft_error(int type)
{
	if (type == TYPE_ER_ARG)
		write(1, "verifier vos arguments\n", 23);
	else if (type == TYPE_ER_MAL)
		write(1, "malloc error\n", 13);
	else if (type == TYPE_ER_MUT)
		write(1, "mutex error\n", 12);
	return (type);
}
