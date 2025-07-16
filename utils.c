/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                           +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:55:00 by user              #+#    #+#             */
/*   Updated: 2025/07/16 21:55:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	print_nb(char *array, int i, int count)
{
	int	num;
	int	mul;

	num = 0;
	mul = 1;
	while (i >= 0)
	{
		num += (array[i] - '0') * mul;
		mul *= 10;
		i--;
	}
	if (count % 2 != 0)
		num *= -1;
	return (num);
}

int	countf(char *str)
{
	int	count;

	count = 0;
	while (*str && *str < 48)
	{
		if (*str == '-')
			count++;
		str++;
	}
	return (count);
}

int	ft_atoi(char *str)
{
	int		i;
	int		count;
	char	array[12];

	i = 0;
	count = countf(str);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			while (*str >= '0' && *str <= '9')
			{
				array[i++] = *str;
				str++;
			}
			break ;
		}
		else if (*str == '+' || *str == ' ' || *str == '-')
			str++;
		else
			break ;
	}
	return (print_nb(array, i - 1, count));
}
