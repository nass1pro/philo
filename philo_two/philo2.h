/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:05:25 by nahaddac          #+#    #+#             */
/*   Updated: 2021/01/09 18:25:32 by nahaddac         ###   ########.fr       */
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
	long int			c_start;
	long int			last_aet;
	long int			time_die;
	long int			limit;
	int					count_eat;
	struct s_targ		*argg;
	int					is_eat;
	pthread_t			t_ph;
	sem_t				*eat;
	long int			current;
}						t_philo;

typedef struct			s_targ
{
	int					nb_ph;
	long int 			start;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	int					must_eat;
	int					philo_dead;
	struct s_philo		*philo;
	sem_t				*fork;
	sem_t				*write_sc;
	int					must_eat_arg;
	int 				cur_eat;
	sem_t				*somebody_dead_m;
	sem_t 				*sem_start;
	sem_t				*sem_grap;
	sem_t				*mutex;
}						t_targ;

void					put_buff(void);
void 					*monitor_flush(void *arg);
char		*st_nbrcpy(char *dst, long int num);
char		*st_strcpy_end(char *dst, char *str);


char					*ft_int_to_char(long long n, char *str);
int						ft_atoi(const char *str);
size_t					ft_strlen(char *str);
t_targ					*init(t_targ *arg, int ac, char **argv);
int						init_philo(t_targ *argt);
int						clear_all(t_targ ar);
int						philo_eat(t_philo *philo);
long int				get_time(void);
int						out_message(int type, t_philo *philo);
char					*get_status(int type);
int						take_fork(t_philo *philo);
int						clean_fork(t_philo *philo);
void					message_tru(t_philo *philo,int type);
int						ft_error(int type);
char					*ft_strncat(char *dest, const char *src, size_t n);
int						philo_sleep_or_think(t_philo *philo, int type);
void					*end_prog_sem(t_philo *philo, int type);
void					*monitor_eat(void *phi);

#endif
