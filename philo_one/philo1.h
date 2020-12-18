/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:00:43 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 04:33:12 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO1_H
# define _PHILO1_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

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
	int					count_eat;
	int					l_fork;
	int					r_fork;
	struct s_targ		*argg;
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
	pthread_mutex_t		*fork;
	pthread_mutex_t		write_sc;
	pthread_mutex_t		mutex;
	int					must_eat_arg;
}						t_targ;

int						ft_atoi(const char *str);
size_t					ft_strlen(char *str);
t_targ					*init(t_targ *arg, int ac, char **argv);
int						init_philo(t_targ *argt);
int						clear_all(t_targ ar);
void					philo_eat(t_philo *philo);
long long				get_time(void);
int						out_message(int type, t_philo *philo);
char					*get_status(int type);
void					take_fork(t_philo *philo);
void					clean_fork(t_philo *philo);
void					message_tru(t_philo *philo,
						char *id, char *time_stamp, int type);
void					ft_philo_dead(int type, t_philo *philo);
int						ft_error(int type);
char					*ft_int_to_char(long long n, char *str);
char					*ft_strncat(char *dest, const char *src, size_t n);

#endif
