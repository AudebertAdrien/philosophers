/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:55:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/28 18:06:42 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


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
	smart_sleep(vars, vars->tt_e);
	pthread_mutex_lock(&(philo->check_meal));
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&(philo->check_meal));
	drop_forks(vars, philo);
}

void	sleeping(t_vars *vars, t_list *philo)
{
	printf_action(vars, philo->philo_id, "sleeping");
	smart_sleep(vars, vars->tt_s);
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
	int			all_eat;

	phi = (t_list *)philo;
	vars = (t_vars *)phi->vars;
	is_alone(vars, phi);
	all_eat = 0;
	while (!is_dead(vars))
	{
		eating(vars, phi);
		pthread_mutex_lock(&(phi->check_meal));
		if (phi->meal_eaten == vars->meal_count)
			all_eat = 1;
		pthread_mutex_unlock(&(phi->check_meal));
		if (all_eat)
			break ;
		sleeping(vars, phi);
		thinking(vars, phi);
	}
	return (NULL);
}
