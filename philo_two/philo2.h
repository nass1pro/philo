/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:05:25 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/20 10:17:53 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO2_H
# define _PHILO2_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>

# define TYPE_FORK		0
# define TYPE_EAT		1
# define TYPE_SLEEP		2
# define TYPE_THINK		3
# define TYPE_DIED		4
# define TYPE_OVER 		5
# define TYPE_ER_MAL	6
# define TYPE_ER_MUT	7
# define TYPE_ER_ARG	8

struct s_targ;

typedef struct			s_philo
{
	int					id;
	long long			c_start;
	long long			last_aet;
	long long			time_die;
	long long 			limit;
	int					count_eat;
	struct s_targ		*argg;
	sem_t 				*mutex;
	int 				is_eat;
	pthread_t			t_ph;
}						t_philo;

typedef struct			s_targ
{
	int					nb_ph;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					must_eat;
	int					philo_dead;
	struct s_philo		*philo;
	sem_t				*fork;
	sem_t				*write_sc;
	int					must_eat_arg;
	sem_t				*somebody_dead_m;
}						t_targ;

char					*ft_int_to_char(long long n, char *str);
int						ft_atoi(const char *str);
size_t					ft_strlen(char *str);
t_targ					*init(t_targ *arg, int ac, char **argv);
int						init_philo(t_targ *argt);
int						clear_all(t_targ ar);
int						philo_eat(t_philo *philo);
long long				get_time(void);
int						out_message(int type, t_philo *philo);
char					*get_status(int type);
int 					take_fork(t_philo *philo);
int 					clean_fork(t_philo *philo);
void					message_tru(t_philo *philo,
						char *id, char *time_stamp, int type);
int						ft_error(int type);
char					*ft_strncat(char *dest, const char *src, size_t n);
int						philo_sleep_or_think(t_philo *philo, int type);

#endif
