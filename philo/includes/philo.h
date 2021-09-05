/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoanne <cjoanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:38 by cjoanne           #+#    #+#             */
/*   Updated: 2021/09/05 05:42:12 by cjoanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define ERROR 1
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define THINKING "is thinking"
# define LFORK	"has taken a left fork"
# define RFORK	"has taken a right fork"

typedef struct s_data
{
	bool			isAllAlive;
	uint32_t		number;
	uint64_t		time;
	uint64_t		toDie;
	uint64_t		toEat;
	uint64_t		toSleep;
	bool			isLimitedMeals;
	uint32_t		mealsCounter;
	uint32_t		startNum;
	uint32_t		ateNum;
	pthread_mutex_t	*mtxs;
	pthread_t		waiter_thread;
	pthread_mutex_t	messenger;
}					t_data;

typedef struct s_philo
{
	uint32_t		pos;
	pthread_t		thread;
	uint64_t		lastMealTime;
	uint32_t		leftForkInd;
	uint32_t		rightForkInd;
	uint32_t		mealsLeft;
	t_data			*data;
}					t_philo;

int			validation_of_args(int argc, char *argv[]);
int			parsing_args(t_data *data, int argc, char *argv[]);

//init
int			init_data(t_data *data);
int			init_philo(t_philo **philo, pthread_t **philo_thread, t_data *data);
void		philo_free(t_philo *philo, pthread_t *philo_thread, t_data *data);

//philo life
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
