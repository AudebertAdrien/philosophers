/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:39:11 by motoko            #+#    #+#             */
/*   Updated: 2023/10/21 19:52:25 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_data(t_vars *vars)
{
	free(vars->fork_tab);
	vars->fork_tab = NULL;
	return (0);
}

int	destroy_mutex(t_vars *vars)
{
	int	i;
	int	is_error;

	i = 0;
	while (i < vars->philo_nb)
	{
		if (pthread_mutex_destroy(&vars->fork_tab[i]))
			return (handle_error("Error : pthread_mutex_destroy\n"));
		i++;
	}
	if (pthread_mutex_destroy(&vars->printf_m))
		handle_error("Error : pthread_mutex_destroy\n");
	if (pthread_mutex_destroy(&vars->check_death))
		handle_error("Error : pthread_mutex_destroy\n");
	
	return (0);
}
