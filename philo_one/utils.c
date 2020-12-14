/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:05:42 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/14 13:50:19 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"
#include <stdio.h>

size_t		ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
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

long long	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (long long)1000) + (t.tv_usec / 1000));
}
