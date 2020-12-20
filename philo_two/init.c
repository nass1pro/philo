/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:42:09 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 10:07:03 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			init_philo(t_targ *argt)
{
	int		i;

	i = 0;
	if (!(argt->philo = malloc(sizeof(t_philo) * argt->nb_ph)))
		return (0);
	while (i <= argt->nb_ph)
	{
		argt->philo[i].id = i + 1;
		argt->philo[i].count_eat = 0;
		argt->philo[i].argg = argt;
		argt->philo[i].is_eat = 0;
		sem_unlink("mutex");
		argt->philo[i].mutex = sem_open("mutex", O_CREAT | O_EXCL, S_IRWXU, 1);
		i++;
	}
	return (1);
}

t_targ		*init_sem(t_targ *ar)
{
	int		i;

	i = 0;
	sem_unlink("fork");
	ar->fork = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, ar->nb_ph);
	sem_unlink("wt");
	ar->write_sc = sem_open("wt", O_CREAT | O_EXCL, S_IRWXU, 1);
	sem_unlink("dead");
	ar->somebody_dead_m = sem_open("dead", O_CREAT | O_EXCL, S_IRWXU, 0);
	ar->philo_dead = 0;
	return (ar);
}

int			ft_is_str_digit(int ac, char **av)
{
	int		i;
	int		j;

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

t_targ		*init(t_targ *time_arg, int ac, char **argv)
{
	int		i;

	i = 0;
	if (ft_is_str_digit(ac, argv))
	{
		time_arg->nb_ph = ft_atoi(argv[1]);
		time_arg->time_to_die = ft_atoi(argv[2]);
		time_arg->time_to_eat = ft_atoi(argv[3]);
		time_arg->time_to_sleep = ft_atoi(argv[4]);
		if (time_arg->nb_ph < 2 || time_arg->time_to_die < 300 ||
			time_arg->time_to_die < 10 || time_arg->time_to_sleep < 10 ||
			time_arg->time_to_die < 10)
			return (NULL);
		if (ac > 5)
			time_arg->must_eat = ft_atoi(argv[5]);
		else
			time_arg->must_eat = 100000;
		return (init_sem(time_arg));
	}
	return (time_arg);
}
