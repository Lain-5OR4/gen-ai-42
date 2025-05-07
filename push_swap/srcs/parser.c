/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_duplicate(int num, int *numbers, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (numbers[i] == num)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (0);
		str++;
	}
	return (result * sign);
}

int	*parse_args(int argc, char **argv, int *size)
{
	int	i;
	int	j;
	int	*numbers;
	int	num;

	*size = 0;
	for (i = 1; i < argc; i++)
		if (!is_number(argv[i]))
			return (NULL);
	numbers = (int *)malloc(sizeof(int) * (argc - 1));
	if (!numbers)
		return (NULL);
	j = 0;
	for (i = 1; i < argc; i++)
	{
		num = ft_atoi(argv[i]);
		if (is_duplicate(num, numbers, j))
		{
			free(numbers);
			return (NULL);
		}
		numbers[j++] = num;
	}
	*size = j;
	return (numbers);
}