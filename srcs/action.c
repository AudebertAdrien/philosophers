/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:39:29 by motoko            #+#    #+#             */
/*   Updated: 2023/10/28 18:24:42 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_vars *vars, int time)
{
	int	i;

	i = timestamp();
	while (!is_dead(vars))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

int	take_forks(t_vars *vars, t_list *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_l]));
		printf_action(vars, philo->philo_id, "has taken a fork");
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_r]));
		printf_action(vars, philo->philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_r]));
		printf_action(vars, philo->philo_id, "has taken a fork");
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_l]));
		printf_action(vars, philo->philo_id, "has taken a fork");
	}
	return (0);
}

int	drop_forks(t_vars *vars, t_list *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(&(vars->fork_tab[philo->fork_l]));
		pthread_mutex_unlock(&(vars->fork_tab[philo->fork_r]));
	}
	else
	{
		pthread_mutex_unlock(&(vars->fork_tab[philo->fork_r]));
		pthread_mutex_unlock(&(vars->fork_tab[philo->fork_l]));
	}
	return (0);
}
