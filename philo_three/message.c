/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:41:12 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/14 12:43:10 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	time_stamp = ft_strncat(time_stamp, " ", 1);
	time_stamp = ft_strncat(time_stamp, id, ft_strlen(id));
	time_stamp = ft_strncat(time_stamp, get_status(type),
				ft_strlen(get_status(type)));
	write(1, time_stamp, ft_strlen(time_stamp));
}

int			end_prog(t_philo *philo)
{
	if (philo->argg->must_eat == philo->count_eat)
	{
		philo->argg->must_eat_arg = 1;
		sem_post(philo->argg->philo_dead);
		ft_philo_dead(TYPE_EAT, philo);
		clean_fork(philo);
	}
	else
	{
		sem_post(philo->argg->philo_dead);
		ft_philo_dead(TYPE_DIED, philo);
		return (1);
	}
	return (1);
}

int			out_message(int type, t_philo *philo)
{
	char	*time_stamp;
	char	*id;

	if (!(time_stamp = malloc(sizeof(char) * 128)))
		return (0);
	if (!(id = malloc(sizeof(char) * 5)))
		return (0);
	sem_wait(philo->argg->write_sc);
	if (get_time() - philo->last_aet > philo->argg->time_to_die ||
		philo->argg->must_eat == philo->count_eat)
	{
		return (end_prog(philo));
	}
	else
		message_tru(philo, id, time_stamp, type);
	sem_post(philo->argg->write_sc);
	free(time_stamp);
	free(id);
	return (1);
}
