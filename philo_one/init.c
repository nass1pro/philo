/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:51:09 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 15:20:36 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int				init_philo(t_targ *argt)
{
	int			i;

	i = -1;
	if (!(argt->philo = malloc(sizeof(t_philo) * argt->nb_ph)))
		return (0);
	while (++i < argt->nb_ph)
	{
		argt->philo[i].id = i + 1;
		argt->philo[i].count_eat = 0;
		argt->philo[i].l_fork = i;
		argt->philo[i].r_fork = (i + 1) % argt->nb_ph;
		argt->philo[i].argg = argt;
		argt->philo[i].is_eat = 0;
		pthread_mutex_init(&argt->philo[i].eat, NULL);
		pthread_mutex_init(&argt->philo[i].mutex, NULL);
		pthread_mutex_init(&argt->philo[i].m_start, NULL);
		pthread_mutex_lock(&argt->philo[i].m_start);
		pthread_mutex_lock(&argt->philo[i].eat);
	}
	return (1);
}

t_targ			*init_mut(t_targ *ar)
{
	int			i;

	i = -1;
	if (!(ar->fork = malloc(sizeof(pthread_mutex_t) * ar->nb_ph)))
		return (NULL);
	while (++i < ar->nb_ph)
		pthread_mutex_init(&ar->fork[i], NULL);
	pthread_mutex_init(&ar->write_sc, NULL);
	pthread_mutex_init(&ar->somebody_dead_m, NULL);
	pthread_mutex_lock(&ar->somebody_dead_m);
	ar->philo_dead = 0;
	ar->must_eat_arg = 0;
	return (ar);
}

int				ft_is_str_digit(int ac, char **av)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j] != '\0')
		{
			if ((av[i][j] >= '0' && av[i][j] <= '9') || av[i][j] == '+' ||
				av[i][j] == '-')
				j++;
			else
				return (0);
		}
		j = 0;
		i++;
	}
	return (1);
}

t_targ			*init(t_targ *time_arg, int ac, char **argv)
{
	int			i;

	i = 0;
	if (ft_is_str_digit(ac, argv))
	{
		time_arg->nb_ph = ft_atoi(argv[1]);
		time_arg->time_to_die = ft_atoi(argv[2]);
		time_arg->time_to_eat = ft_atoi(argv[3]);
		time_arg->time_to_sleep = ft_atoi(argv[4]);
		if (time_arg->nb_ph < 2 || time_arg->time_to_die < 60 ||
			time_arg->time_to_sleep < 60 || time_arg->time_to_eat < 60 ||
			time_arg->nb_ph > 200)
			return (NULL);
		if (ac > 5)
		{
			time_arg->must_eat = ft_atoi(argv[5]);
			if (time_arg->must_eat < 0)
				return (NULL);
		}
		else
			time_arg->must_eat = 0;
		return (init_mut(time_arg));
	}
	return (NULL);
}
