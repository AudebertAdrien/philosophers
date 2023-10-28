/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:02:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/28 17:58:45 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_vars *vars, t_list *philo_lst)
{
	int	i;

	i = 0;
	while (++i < vars->philo_nb)
	{
		pthread_mutex_lock(&(philo_lst[i].check_meal));
		if (philo_lst[i].meal_eaten != vars->meal_count)
		{
			pthread_mutex_lock(&(vars->check_death));
			if (time_diff(philo_lst[i].last_meal, timestamp()) > vars->tt_d)
			{
				printf_action(vars, philo_lst[i].philo_id, "DEAD");
				vars->dieded = 1;
			}
			pthread_mutex_unlock(&(vars->check_death));
		}
		pthread_mutex_unlock(&(philo_lst[i].check_meal));
	}
}

int	check_meal(t_vars *vars, t_list *philo_lst)
{
	int	all_eat;
	int	i;

	i = 0;
	all_eat = 0;
	while (i < vars->philo_nb && vars->meal_count > 0)
	{
		pthread_mutex_lock(&(philo_lst[i].check_meal));
		if (philo_lst[i].meal_eaten == vars->meal_count)
			all_eat++;
		pthread_mutex_unlock(&(philo_lst[i].check_meal));
		i++;
	}
	if (all_eat == vars->philo_nb)
		return (1);
	return (0);
}

void	death_checker(t_vars *vars, t_list *philo_lst)
{
	while (1)
	{
		check_death(vars, philo_lst);
		if (is_dead(vars))
			return ;
		if (check_meal(vars, philo_lst))
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
		pthread_mutex_lock(&(vars->check_death));
		vars->philo_lst[i].last_meal = timestamp();
		pthread_mutex_unlock(&(vars->check_death));
		is_error = pthread_create(&(vars->philo_lst[i]).thread,
				NULL, &routine, &vars->philo_lst[i]);
		if (is_error)
			handle_error("Error : pthread_create");
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
