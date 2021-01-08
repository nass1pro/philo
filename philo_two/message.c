/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:14:37 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/08 06:59:42 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

char		*ft_int_to_char(long long n, char *str)
{
	char	c;
	int		length;

	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	length = 0;
	while (n != 0)
	{
		c = '0' + (n % 10);
		n = (n / 10);
		str[length] = c;
		length++;
	}
	str[length] = '\0';
	return (str);
}

char		*revers_str(char *str)
{
	int		i;
	int		j;
	char	swap;

	i = ft_strlen(str) - 1;
	j = 0;
	while (i > j)
	{
		swap = str[i];
		str[i] = str[j];
		str[j] = swap;
		i--;
		j++;
	}
	return (str);
}

void		message_tru(t_philo *philo, char *id, char *time_stamp, int type)
{
	if (type  == TYPE_OVER)
		return ;
	time_stamp = ft_int_to_char(get_time() - philo->c_start, time_stamp);
	id = ft_int_to_char(philo->id, id);
	revers_str(time_stamp);
	revers_str(id);
	time_stamp = ft_strncat(time_stamp, " ", 1);
	time_stamp = ft_strncat(time_stamp, id, 3);
	time_stamp = ft_strncat(time_stamp, get_status(type),
				ft_strlen(get_status(type)));
	write(1, time_stamp, ft_strlen(time_stamp));
	if (type == TYPE_FORK)
		write(1, time_stamp, ft_strlen(time_stamp));
}

int			out_message(int type, t_philo *philo)
{
	char	time_stamp[128];
	char	id[5];

	time_stamp[0] = '\0';

	if (philo->count_eat > philo->argg->must_eat && philo->argg->must_eat)
		return (1);
	if (sem_wait(philo->argg->write_sc))
		return (1);
	if (type == TYPE_EAT)
		message_tru(philo, id, time_stamp, TYPE_FORK);
	message_tru(philo, id, time_stamp, type);
	if (type != TYPE_DIED && type != TYPE_OVER)
		if (sem_post(philo->argg->write_sc))
			return (1);
	return (0);
}
