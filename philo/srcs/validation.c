#include "philo.h"

static int	check_for_number(char *str)
{
	long long	num;

	if (!str)
		return (ERROR);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			return (ft_error("Error: neagtive sign\n"));
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (0);
	else
		return (ft_error("Error: some argument not a number"));
}

int	validation_of_args(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		return(ft_error("Error: wrong amonut of arguments\n"));
	i = 1;
	while (i < argc)
	{
		if (check_for_number(argv[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (0);
}