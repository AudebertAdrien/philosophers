/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:55:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/21 19:58:46 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_meals(t_vars *vars, t_list *philo)
{
	//pthread_mutex_lock(&vars->printf_m);	
	printf("%d : meal eaten : %d\n", philo->philo_id, philo->meal_eaten);
	//pthread_mutex_unlock(&vars->printf_m);	
}

int	take_forks(t_vars *vars, t_list *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_l]));
		printf_action(vars, philo->philo_id, "has taken a fork l");
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_r]));
		printf_action(vars, philo->philo_id, "has taken a fork r");
	}
	else
	{
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_r]));
		printf_action(vars, philo->philo_id, "has taken a fork r");
		pthread_mutex_lock(&(vars->fork_tab[philo->fork_l]));
		printf_action(vars, philo->philo_id, "has taken a fork l");
	}
	return (0);
}

void            smart_sleep(int time, t_vars *rules)
{
	int i;

	i = timestamp();
	while (!(rules->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

int	eating(t_vars *vars, t_list *philo)
{
	take_forks(vars, philo);

	pthread_mutex_lock(&(vars->check_death));
	printf_action(vars, philo->philo_id, "eating");
	philo->last_meal = timestamp();
	//usleep(philo->vars->tt_e * 1000);
	pthread_mutex_unlock(&(vars->check_death));

	smart_sleep(philo->vars->tt_e, vars);
	philo->meal_eaten += 1;

	pthread_mutex_unlock(&(vars->fork_tab[philo->fork_r]));
	pthread_mutex_unlock(&(vars->fork_tab[philo->fork_l]));
	//printf_action(vars, philo->philo_id, "has DROP a fork");

	//print_meals(vars, philo);
}

int	sleeping(t_vars *vars, t_list *philo)
{
	//usleep(philo->vars->tt_s * 1000);
	smart_sleep(philo->vars->tt_s, vars);
	printf_action(vars, philo->philo_id, "sleeping");
}

int	thinking(t_vars *vars, t_list *philo)
{
	printf_action(vars, philo->philo_id, "thinking");
}

void	*routine(void *philo)
{
	t_list		*phi;
	t_vars		*vars;
	int		is_error;
	struct timeval	tv;

	phi = (t_list *)philo;
	vars = (t_vars *)phi->vars;

	while (!vars->dieded)
	{
		eating(vars, phi);
		if (phi->meal_eaten == vars->meal_count)
			break;
		sleeping(vars, phi);
		thinking(vars, phi);
	}
}
