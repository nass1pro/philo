/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:49:19 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 10:48:26 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (long long)1000) + (t.tv_usec / 1000));
}

void		philo_sleep_or_think(t_philo *philo, int type)
{
	long long ti;

	if (type == TYPE_SLEEP)
	{
		if (philo->argg->time_to_eat > philo->argg->time_to_die ||
			philo->argg->time_to_sleep >= philo->argg->time_to_die)
		{
			ti = philo->argg->time_to_die - (get_time() - philo->last_aet);
			usleep(ti * 1000);
			out_message(type, philo);
			return ;
		}
		else
		{
			usleep(philo->argg->time_to_sleep * 1000);
			out_message(type, philo);
		}
	}
	else
		out_message(type, philo);
}

char		*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (j < n && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

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

size_t		ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
