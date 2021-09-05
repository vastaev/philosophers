/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoanne <cjoanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 04:56:42 by cjoanne           #+#    #+#             */
/*   Updated: 2021/09/05 04:56:43 by cjoanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if ((c == ' ' ) || (c == '\n') || (c == '\t') \
	|| (c == '\v') || (c == '\f') || (c == '\r'))
		return (1);
	return (0);
}

uint32_t	ft_atoi_long(const char *str)
{
	uint32_t	res;

	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 - (*str++ - '0');
	return (res * -1);
}
