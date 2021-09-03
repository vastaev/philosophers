#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define ERROR 1

typedef struct s_philo
{
	int	state;
	uint32_t		pos;
	pthread_t		thread;
	uint64_t		birth;
	uint64_t		lastMeal;
	pthread_mutex_t	*lFork;
	pthread_mutex_t	*rFork;
	uint32_t		mealsCount;
	void			*data;
}					t_philo;

typedef struct s_data
{
	uint32_t		number;
	uint64_t		toDie;
	uint64_t		toEat;
	uint64_t		toSleep;
	bool			isLimitedMeals;
	uint32_t		mealsCounter;

	t_philo			*philos;
	pthread_mutex_t	*mtxs;
	pthread_t		waiter_thread;
	pthread_t		messager;

}					t_data;



int			validation_of_args(int argc, char *argv[]);
int			parsing_args(t_data *data, int argc, char *argv[]);

//init
int			initialize_data(t_data *data);
void		initialize_philos(t_data *data);

//libft funcs
int			ft_isdigit(char c);
int			ft_isspace(char c);
uint64_t	ft_atoi_long(const char *str);

//utils
int			ft_error(char *str);
uint64_t	get_time(uint64_t start);



#endif
