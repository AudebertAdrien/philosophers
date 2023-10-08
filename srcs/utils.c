/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:58 by motoko            #+#    #+#             */
/*   Updated: 2023/10/08 15:23:25 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_tab(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		printf("id %d\n", vars->philo_lst[i].philo_id);
		i++;
	}
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	handle_error(char *msg)
{
	ft_putstr(msg);
	exit(EXIT_FAILURE);
}
