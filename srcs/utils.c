/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:58 by motoko            #+#    #+#             */
/*   Updated: 2023/10/15 13:48:18 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printf_action(t_vars *vars, int id, char *str)
{
	pthread_mutex_lock(&vars->printf_m);	
	printf("%d : %s\n", id, str);
	pthread_mutex_unlock(&vars->printf_m);	
}

void	print_tab(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		printf_action(vars, vars->philo_lst[i].philo_id, "id");
		i++;
	}
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}
