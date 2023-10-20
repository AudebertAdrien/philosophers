/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:02:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/20 16:36:05 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	create_threads(t_vars *vars)
{
	int	is_error;
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		is_error = pthread_create(&(vars->philo_lst[i]).thread,
				NULL, &routine, &vars->philo_lst[i]);
		if (is_error)
			handle_error("Error : pthread_create");
		i++;
	}
	return (0);
}

void	death_checker(t_vars *vars, t_list *philo_lst)
{
	int	is_dead = 0;
	int	i = 0;

	while(1)	
	{
		while (i < vars->philo_nb)
		{
			if (time_diff(philo_lst[i].last_meal, timestamp()) > vars->tt_d)
			{
				printf_action(vars, philo_lst[i].philo_id, "DEAD");	
				return ;
			}
			i++;
		}
	}
}

pthread_t	join_threads(t_vars *vars)
{
	int	is_error;
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		is_error = pthread_join(vars->philo_lst[i].thread, NULL);
		if (is_error)
			handle_error("Error : pthread_create");
		i++;
	}
	death_checker(vars, vars->philo_lst);
	return (0);
}
