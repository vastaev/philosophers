#include "philo.h"

uint64_t	get_time(uint64_t start)
{
	struct timeval tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000 - start);
}

void	ft_usleep(u_int32_t n)
{
	struct timeval	i;
	struct timeval	j;

	gettimeofday(&i, NULL);
	while (42)
	{
		gettimeofday(&j, NULL);
		if (((j.tv_usec - i.tv_usec + (j.tv_sec - i.tv_sec) * 1000000)) > n)
			break ;
		usleep(10);
	}
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (ERROR);
}