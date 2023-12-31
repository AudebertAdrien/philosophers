/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:39:11 by motoko            #+#    #+#             */
/*   Updated: 2023/10/29 19:23:50 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_data(t_vars *vars)
{
	free(vars->fork_tab);
	free(vars->philo_lst);
	vars->fork_tab = NULL;
	vars->philo_lst = NULL;
	return (0);
}

int	destroy_mutex(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		if (pthread_mutex_destroy(&vars->fork_tab[i]))
			return (handle_error("Error : pthread_mutex_destroy\n"));
		if (pthread_mutex_destroy(&vars->philo_lst[i].check_meal))
			handle_error("Error : pthread_mutex_destroy\n");
		i++;
	}
	if (pthread_mutex_destroy(&vars->printf_m))
		handle_error("Error : pthread_mutex_destroy\n");
	if (pthread_mutex_destroy(&vars->check_death))
		handle_error("Error : pthread_mutex_destroy\n");
	return (0);
}
