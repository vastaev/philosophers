/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:36 by cjoanne           #+#    #+#             */
/*   Updated: 2021/10/06 05:48:53 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	creat_prcs(t_philo *philo, t_data *data);
static void	waiter_actions(t_data *data);
static int	data_to_phil(t_philo *philo, t_data *data);

int	main(int argc, char *argv[])
{
	t_data		*data;
	t_philo		*philo;

	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo));
	if (validation_of_args(argc, argv) == ERROR)
		return (ERROR);
	if (parsing_args(data, argc, argv) == ERROR)
		return (ERROR);
	if (init_data(data) == ERROR)
		return (ERROR);
	data_to_phil(philo, data);
	creat_prcs(philo, data);
	waiter_actions(data);
	return (0);
}

static int	data_to_phil(t_philo *philo, t_data *data)
{
	philo->pos = 1;
	philo->data = data;
	philo->meals_left = 0;
	philo->thread = malloc(sizeof(pthread_t));
	if (philo->data->is_limited_meals == true)
		philo->meals_left = data->meals_counter;
	return (0);
}

static int	creat_prcs(t_philo *philo, t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->number)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			ft_error("Error: fork fail\n");
		if (data->pids[i])
			philo->pos++;
		else
		{
			child_philos(philo);
			printf("Error\n");
			exit(1);
		}
		i++;
	}
	return (0);
}

static void	waiter_actions(t_data *data)
{
	uint32_t	i;
	uint32_t	k;
	int			res_status;

	i = 0;
	k = 0;
	while (k < data->number)
	{
		waitpid(-1, &res_status, 0);
		if (WEXITSTATUS(res_status) != 0)
			while (i < data->number)
				kill(data->pids[i++], SIGKILL);
		k++;
	}
}
