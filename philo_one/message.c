/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:35:21 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/14 13:36:33 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

#define PHILO_PUT_BUF_SIZE 20000

static char		g_buf[PHILO_PUT_BUF_SIZE + 256] = {'\0'};
static char		*g_curr = g_buf;

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
	return ("\0");
}

char		*st_nbrcpy(char *dst, long int num)
{
	if (num > 9)
		dst = st_nbrcpy(dst, num / 10);
	 dst[0] = num % 10 + '0';
	 return (dst + 1);
 }

char		*st_strcpy_end(char *dst, char *str)
{
	while (*str != '\0')
		*dst++ = *str++;
	return (dst);
}

void put_buff(void)
{
	write(STDOUT_FILENO, g_buf, g_curr - g_buf);
	g_curr = g_buf;
	g_buf[0] = '\0';
}

void		message_tru(t_philo *philo, int type)
{
	if (type  == TYPE_OVER)
		return ;
	g_curr = st_nbrcpy(g_curr,(get_time() - philo->argg->start));
	g_curr = st_strcpy_end(g_curr, " ");
	g_curr = st_nbrcpy(g_curr,philo->id);
	g_curr = st_strcpy_end(g_curr, get_status(type));
	if (g_curr - g_buf > PHILO_PUT_BUF_SIZE || type == TYPE_DIED)
		put_buff();
}

int			out_message(int type, t_philo *philo)
{
	if (philo->count_eat > philo->argg->must_eat && philo->argg->must_eat)
		return (1);
	pthread_mutex_lock(&philo->argg->write_sc);
	message_tru(philo, type);
	if (type != TYPE_DIED && type != TYPE_OVER)
		pthread_mutex_unlock(&philo->argg->write_sc);
	return (1);
}
