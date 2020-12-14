/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:51:09 by nahaddac          #+#    #+#             */
/*   Updated: 2020/11/13 12:06:48 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int				init_philo(t_targ *argt)
{
	int		i;

	i = 0;
	if (!(argt->philo = malloc(sizeof(t_philo) * argt->nb_ph)))
		return (0);
	while (i <= argt->nb_ph)
	{
		argt->philo[i].id = i + 1;
		argt->philo[i].count_eat = 0;
		argt->philo[i].l_fork = i;
		argt->philo[i].r_fork = (i + 1) % argt->nb_ph;
		argt->philo[i].argg = argt;
		i++;
	}
	return (1);
}

t_targ			*init_mut(t_targ *ar)
{
	int		i;

	i = 0;
	pthread_mutex_init(&ar->write_sc, NULL);
	ar->philo_dead = 0;
	ar->must_eat_arg = 0;
	while (i <= ar->nb_ph)
		pthread_mutex_init(&ar->fork[i++], NULL);
	return (ar);
}

int				ft_is_str_digit(int ac, char **av)
{
	int i;
	int j;

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
		if (time_arg->nb_ph < 3 || time_arg->time_to_die < 100 ||
			time_arg->time_to_sleep < 10 || time_arg->must_eat > 0 ||
			time_arg->time_to_eat < 10)
			return (NULL);
		if (!(time_arg->fork =
			malloc(sizeof(pthread_mutex_t) * time_arg->nb_ph)))
			return (NULL);
		if (ac > 5)
			time_arg->must_eat = ft_atoi(argv[5]);
		else
			time_arg->must_eat = 100000;
		return (init_mut(time_arg));
	}
	return (time_arg);
}
