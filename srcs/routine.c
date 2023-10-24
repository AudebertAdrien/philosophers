/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:55:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/24 15:31:26 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_meals(t_vars *vars, t_list *philo)
{
	pthread_mutex_lock(&vars->printf_m);	
	printf("%d : meal eaten : %d\n", philo->philo_id, philo->meal_eaten);
	pthread_mutex_unlock(&vars->printf_m);	
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

void            smart_sleep(t_vars *vars, int time)
{
	int i;

	i = timestamp();
	while (!is_dead(vars))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	eating(t_vars *vars, t_list *philo)
{
	take_forks(vars, philo);

	pthread_mutex_lock(&(vars->check_death));
	printf_action(vars, philo->philo_id, "eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(vars->check_death));

	//smart_sleep(vars, philo->vars->tt_e);
	usleep(philo->vars->tt_e * 1000);

	pthread_mutex_lock(&(philo->check_meal));
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&(philo->check_meal));

	drop_forks(vars, philo);
	print_meals(vars, philo);
}

void	sleeping(t_vars *vars, t_list *philo)
{
	printf_action(vars, philo->philo_id, "sleeping");
	usleep(philo->vars->tt_s * 1000);
	//smart_sleep(vars, philo->vars->tt_s);
}

void	thinking(t_vars *vars, t_list *philo)
{
	printf_action(vars, philo->philo_id, "thinking");
}

int	is_dead(t_vars *vars)
{
	int	is_dead; 

	pthread_mutex_lock(&(vars->check_death));
	is_dead = vars->dieded;
	pthread_mutex_unlock(&(vars->check_death));
	return (is_dead);
}

void	*routine(void *philo)
{
	t_list		*phi;
	t_vars		*vars;

	phi = (t_list *)philo;
	vars = (t_vars *)phi->vars;
	if (vars->philo_nb == 1)
	{
		pthread_mutex_lock(&(vars->check_death));
		printf_action(vars, phi->philo_id, "DEAD");	
		vars->dieded = 1;
		pthread_mutex_unlock(&(vars->check_death));
	}

	int	boo = 0;
	while (!is_dead(vars))
	{
		eating(vars, phi);
		pthread_mutex_lock(&(phi->check_meal));
		if (phi->meal_eaten == vars->meal_count)
			boo= 1;
		pthread_mutex_unlock(&(phi->check_meal));
		if (boo)
			break;
		sleeping(vars, phi);
		thinking(vars, phi);
	}
	return (NULL);
}
