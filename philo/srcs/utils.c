#include "philo.h"

uint64_t	get_time(uint64_t start)
{
	struct timeval tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000 - start);
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (ERROR);
}