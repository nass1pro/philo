/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:41:40 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/15 13:06:33 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

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
	long long			limit;
	int					count_eat;
	struct s_targ		*argg;
	sem_t				*mutex;
	int					is_eat;
	pthread_t			t_ph;
	sem_t				*eat;
	int					must_eat;
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
	int					cur_eat;
	sem_t				*somebody_dead_m;
	sem_t				*end;
	sem_t				*sem_start;
	sem_t				*sem_grap;
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
int						take_fork(t_philo *philo);
int						clean_fork(t_philo *philo);
void					message_tru(t_philo *philo,
						char *id, char *time_stamp, int type);
int						ft_error(int type);
char					*ft_strncat(char *dest, const char *src, size_t n);
int						philo_sleep_or_think(t_philo *philo, int type);
void					*end_prog_sem(t_philo *philo, int type);
void					*monitor(void *philo_v);
int						start_m(t_targ *arg);
#endif
