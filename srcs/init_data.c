/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:35:08 by motoko            #+#    #+#             */
/*   Updated: 2023/10/12 15:20:00 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex_tab(t_vars *vars)
{
	int	is_error;
	int	i;

	i = 0;
	vars->fork_tab = ft_calloc(vars->philo_nb, sizeof(pthread_mutex_t));
	while (i < vars->philo_nb)
	{
		is_error = pthread_mutex_init(&(vars->fork_tab)[i], NULL);
		if (is_error)
			handle_error("Error : pthread_mutex_init\n", NULL);
		i++;
	}
	return (0);
}

int	assign_mutex(t_vars *vars, int *i)
{
	if (*i == vars->philo_nb - 1)
	{
		vars->philo_lst[*i].fork_r = &vars->fork_tab[*i];
		vars->philo_lst[*i].fork_l = &vars->fork_tab[0];
	}
	else
	{
		vars->philo_lst[*i].fork_r = &vars->fork_tab[*i];
		vars->philo_lst[*i].fork_l = &vars->fork_tab[*i + 1];
	}
	return (0);
}

int	create_tab(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->philo_nb)
	{
		vars->philo_lst[i].philo_id = i + 1;
		vars->philo_lst[i].vars = vars;
		assign_mutex(vars, &i);
		i++;
	}
	return (0);
}