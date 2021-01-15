/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:14:37 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 18:30:32 by nahaddac         ###   ########.fr       */
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
	if (type == TYPE_OVER)
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
	message_tru(philo, type);
	if (type != TYPE_DIED && type != TYPE_OVER)
		sem_post(philo->argg->write_sc);
	return (0);
}
