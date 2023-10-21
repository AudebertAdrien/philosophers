/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:02:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/21 19:54:55 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	death_checker(t_vars *vars, t_list *philo_lst)
{
	int	is_dead = 0;
	int	i = 0;

	while(1)	
	{
		i = 0;
		while (i < vars->philo_nb)
		{
			pthread_mutex_lock(&(vars->check_death));
			if (time_diff(philo_lst[i].last_meal, timestamp()) > vars->tt_d)
			{
				/*
				printf("1last : %d\n", philo_lst[i].last_meal);
				printf("1timestamp : %d\n", timestamp());
				printf("1tt_d : %d\n", vars->tt_d);
				printf("1time diff : %d\n", time_diff(philo_lst[i].last_meal, timestamp()));
				*/
				printf_action(vars, philo_lst[i].philo_id, "DEAD");	
				vars->dieded = 1;
			}
			pthread_mutex_unlock(&(vars->check_death));
			usleep(100);
			i++;
		}
		if (vars->dieded)
			return ;
	}
}

int	create_threads(t_vars *vars)
{
	int	is_error;
	int	i;

	i = 0;

	vars->first_timestamp = timestamp();
	while (i < vars->philo_nb)
	{
		is_error = pthread_create(&(vars->philo_lst[i]).thread,
				NULL, &routine, &vars->philo_lst[i]);
		if (is_error)
			handle_error("Error : pthread_create");
		vars->philo_lst[i].last_meal = timestamp();
		i++;
	}
	death_checker(vars, vars->philo_lst);
	return (0);
}

int	join_threads(t_vars *vars)
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
	return (0);
}
