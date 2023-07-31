/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:30:43 by khorike           #+#    #+#             */
/*   Updated: 2023/07/31 19:47:44 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}

static long	atat(const char **nptr, int sign)
{
	size_t	i;
	size_t	j;
	size_t	digit;

	i = 0;
	j = 0;
	while ((*nptr)[i] && (*nptr)[i] >= '0' && (*nptr)[i] <= '9')
	{
		digit = (*nptr)[i] - '0';
		if (sign != -1 && ((j > LONG_MAX / 10)
				|| (j == LONG_MAX / 10 && digit > LONG_MAX % 10)))
			return (LONG_MAX);
		if (sign == -1 && ((j > LONG_MAX / 10)
				|| (j == LONG_MAX / 10 && digit > LONG_MAX % 10 + 1)))
			return (LONG_MIN);
		j = j * 10 + digit;
		i++;
	}
	*nptr += i;
	return (j * sign);
}

long	ft_strtol(const char *str, char **endptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	result = atat(&str, sign);
	if (endptr != NULL)
		*endptr = (char *)str;
	return (result);
}

bool	is_valid_number(char *arg, int *status)
{
	char	*endptr;
	long	val;

	val = ft_strtol(arg, &endptr);
	if (*endptr != '\0' || val == LONG_MIN || val == LONG_MAX)
		return (false);
	val = val % 256;
	if (val < 0)
		val = val + 256;
	*status = (int)val;
	return (true);
}

int	ft_ms_exit(char **args)
{
	char	*arg;
	int		status;

	arg = args[0];
	printf("exit\n");
	if (args[0] == NULL)
		exit(0);
	else if (args[1] != NULL)
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 26);
		return (FAILURE);
	}
	if (is_valid_number(arg, &status))
		exit(status);
	else
	{
		write(STDERR_FILENO, "exit: numeric argument required\n", 33);
		exit (255);
	}
}
