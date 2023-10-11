/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:08:21 by aaudeber          #+#    #+#             */
/*   Updated: 2023/10/11 19:06:49 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_overflow(int res, int num, int sign)
{
	int	tmp;

	if (res == 0 || num == 0)
		return (0);
	tmp = (res * 10) + num;
	if (sign)
	{
		if ((tmp - num) / 10 == res && tmp > 0)
			return (0); 
		else
			return (1);
	}
	tmp *= -1;
	if ((tmp + num) / 10 == res * -1 && tmp < 0)
		return (0);
	else
		return (1);
	return (0);
}

int	ft_atoi(t_vars *vars, const char *nptr)
{
	int	res;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while ((nptr[i] && (nptr[i] >= 9 && nptr[i] <= 13)) || nptr[i] == 32)
		i++;
	if (nptr[i] && (nptr[i] == 45 || nptr[i] == 43))
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (is_overflow(res, nptr[i] - 48, sign))
			vars->error = 1;
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}
