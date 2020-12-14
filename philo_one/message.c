/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:35:21 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/14 13:38:09 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

char		*get_status(int type)
{
	if (type == TYPE_FORK)
		return (" has taken a fork\n");
	else if (type == TYPE_EAT)
		return (" is eating\n");
	else if (type == TYPE_SLEEP)
		return (" is sleeping\n");
	else if (type == TYPE_THINK)
		return (" is thinking\n");
	else if (type == TYPE_DIED)
		return (" died\n");
	return (" must eat count reached\n");
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
	time_stamp = ft_int_to_char(get_time() - philo->c_start, time_stamp);
	id = ft_int_to_char(philo->id, id);
	revers_str(time_stamp);
	revers_str(id);
	time_stamp = ft_strncat(time_stamp, " ", 2);
	time_stamp = ft_strncat(time_stamp, id, ft_strlen(id));
	time_stamp = ft_strncat(time_stamp, get_status(type),
				ft_strlen(get_status(type)));
	write(1, time_stamp, ft_strlen(time_stamp));
}

static void	out_message_two(t_philo *philo)
{
	if (philo->argg->must_eat == philo->count_eat)
	{
		philo->argg->must_eat_arg = 1;
		philo->argg->philo_dead = 1;
		usleep(philo->argg->time_to_eat * 1000);
		ft_philo_dead(TYPE_EAT, philo);
		ft_philo_dead(TYPE_OVER, philo);
	}
	else
	{
		philo->argg->philo_dead = 1;
		ft_philo_dead(TYPE_DIED, philo);
	}
}

int			out_message(int type, t_philo *philo)
{
	char		*time_stamp;
	char		*id;

	if (!(time_stamp = malloc(sizeof(char) * 128)))
		return (0);
	if (!(id = malloc(sizeof(char) * 5)))
		return (0);
	pthread_mutex_lock(&philo->argg->write_sc);
	if (philo->argg->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->argg->write_sc);
		return (0);
	}
	if (get_time() - philo->last_aet > philo->argg->time_to_die ||
		philo->argg->must_eat == philo->count_eat)
	{
		out_message_two(philo);
	}
	else
		message_tru(philo, id, time_stamp, type);
	pthread_mutex_unlock(&philo->argg->write_sc);
	free(time_stamp);
	free(id);
	return (1);
}
