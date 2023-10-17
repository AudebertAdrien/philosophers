/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:55:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/17 13:22:36 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printf_action(t_vars *vars, int id, char *str)
{
	struct timeval	tv;
	long long int	diff_time;

	gettimeofday(&tv, NULL);
	diff_time =  (tv.tv_sec * 1000 + tv.tv_usec / 1000) - vars->philo_lst[id - 1].start_t;

	pthread_mutex_lock(&vars->printf_m);	
	printf("%lld ms %d : %s\n",diff_time, id, str);
	pthread_mutex_unlock(&vars->printf_m);	
}

int	print_meals(t_vars *vars, t_list *philo)
{
	pthread_mutex_lock(&vars->printf_m);	
	printf("%d : meal eaten : %d\n", philo->philo_id, philo->meal_eaten);
	pthread_mutex_unlock(&vars->printf_m);	
}

int	eating(t_vars *vars, t_list *philo)
{
	pthread_mutex_lock(&(vars->fork_tab[philo->fork_r]));
	pthread_mutex_lock(&(vars->fork_tab[philo->fork_l]));

	printf_action(vars, philo->philo_id, "has taken a fork");
	printf_action(vars, philo->philo_id, "eating");

	philo->meal_eaten += 1;
	usleep(philo->vars->tt_e * 1000);

	pthread_mutex_unlock(&(vars->fork_tab[philo->fork_r]));
	pthread_mutex_unlock(&(vars->fork_tab[philo->fork_l]));

	print_meals(vars, philo);
}

int	sleeping(t_vars *vars, t_list *philo)
{
	usleep(philo->vars->tt_s * 1000);
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
	long long int	start_t;

	phi = (t_list *)philo;
	vars = (t_vars *)phi->vars;
	gettimeofday(&tv, NULL);

	start_t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	phi->start_t = start_t;

	while (1)
	{
		eating(vars, phi);
		if (phi->meal_eaten == vars->meal_count)
			break;
		sleeping(vars, phi);
		thinking(vars, phi);
	}
}
