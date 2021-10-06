/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:38 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 05:48:07 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define ERROR 1
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define THINKING "is thinking"
# define FORK	"has taken a fork"

typedef struct s_data
{
	uint32_t		number;
	uint64_t		time;
	uint64_t		to_die;
	uint64_t		to_eat;
	uint64_t		to_sleep;
	bool			is_limited_meals;
	uint32_t		meals_counter;
	sem_t			*forks;
	sem_t			*both_forks;
	sem_t			*messenger;
	pid_t			*pids;
}					t_data;

typedef struct s_philo
{
	uint32_t		pos;
	pthread_t		thread;
	uint64_t		last_meal_time;
	uint32_t		meals_left;
	t_data			*data;
}					t_philo;

int			validation_of_args(int argc, char *argv[]);
int			parsing_args(t_data *data, int argc, char *argv[]);

//init
int			init_data(t_data *data);

//philo life
void		child_philos(t_philo *philo);
void		*philo_life(void *philosopher);

//libft funcs
int			ft_isdigit(char c);
int			ft_isspace(char c);
uint32_t	ft_atoi_long(const char *str);

//utils
int			ft_error(char *str);
uint64_t	get_time(uint64_t start);
void		ft_usleep(uint64_t n);

#endif
