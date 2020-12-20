/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 10:12:54 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 10:53:39 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			ft_error(int type)
{
	if (type == TYPE_ER_ARG)
		write(1, "verifier vos arguments\n", 23);
	else if (type == TYPE_ER_MAL)
		write(1, "malloc error\n", 13);
	else if (type == TYPE_ER_MUT)
		write(1, "sema error\n", 11);
	return (type);
}
