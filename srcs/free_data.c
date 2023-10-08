/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:39:11 by motoko            #+#    #+#             */
/*   Updated: 2023/10/08 15:52:33 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutex(t_vars *vars)
{
	int	i;
	int	is_error;

	i = 0;
	while (i < vars->philo_nb)
	{
		is_error = pthread_mutex_destroy(&vars->fork_tab[i]);
		if (is_error)
			handle_error("error : pthread_mutex_destroy\n");
		i++;
	}
	return (0);
}

void	handle_error(char *msg)
{
	ft_putstr(msg);
	exit(EXIT_FAILURE);
}

int	free_data(t_vars *vars)
{
	free(vars->fork_tab);
	vars->fork_tab = NULL;
	return (0);
}
