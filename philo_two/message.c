/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:14:37 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/09 00:53:31 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"
#define PHILO_PUT_BUF_SIZE 20000

static char		g_buf[PHILO_PUT_BUF_SIZE + 256] = {'\0'};
static char		*g_curr = g_buf;

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

void put_buff(void)
{
	write(STDOUT_FILENO, g_buf, g_curr - g_buf);
	g_curr = g_buf;
	g_buf[0] = '\0';
}

int			out_message(int type, t_philo *philo)
{
	if (philo->count_eat > philo->argg->must_eat && philo->argg->must_eat)
		return (1);
	if (sem_wait(philo->argg->write_sc))
		return (1);
	if (type == TYPE_EAT)
	{
		message_tru(philo, TYPE_FORK);
		message_tru(philo, TYPE_FORK);
	}
	message_tru(philo,type);
	if (type != TYPE_DIED && type != TYPE_OVER)
	{
		if (sem_post(philo->argg->write_sc))
			return (1);
	}
	return (0);
}




// voidmessage_tru(t_philo *philo, char *id, char *time_stamp, int type)
// {
	// if (type  == TYPE_OVER)
	// return ;
	// time_stamp = ft_int_to_char(get_time() - philo->c_start, time_stamp);
	// id = ft_int_to_char(philo->id, id);
	// revers_str(time_stamp);
	// revers_str(id);
	// time_stamp = ft_strncat(time_stamp, " ", 1);
	// time_stamp = ft_strncat(time_stamp, id, 3);
	// time_stamp = ft_strncat(time_stamp, get_status(type),
	// ft_strlen(get_status(type)));
	// write(1, time_stamp, ft_strlen(time_stamp));
	// if (type == TYPE_FORK)
// 		write(1, time_stamp, ft_strlen(time_stamp));
// }
//
		// intout_message(int type, t_philo *philo)
		// {
		// chartime_stamp[128];
		// charid[5];
		//
		// time_stamp[0] = '\0';
		//
		// if (philo->count_eat > philo->argg->must_eat && philo->argg->must_eat)
		// return (1);
		// if (sem_wait(philo->argg->write_sc))
		// return (1);
		// if (type == TYPE_EAT)
		// message_tru(philo, id, time_stamp, TYPE_FORK);
		// message_tru(philo, id, time_stamp, type);
		// if (type != TYPE_DIED && type != TYPE_OVER)
		// if (sem_post(philo->argg->write_sc))
		// return (1);
		// return (0);
// }
