/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:58 by motoko            #+#    #+#             */
/*   Updated: 2023/10/28 17:54:08 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_alone(t_vars *vars, t_list *phi)
{
	if (vars->philo_nb == 1)
	{
		pthread_mutex_lock(&(vars->check_death));
		printf_action(vars, phi->philo_id, "DEAD");
		vars->dieded = 1;
		pthread_mutex_unlock(&(vars->check_death));
	}
}

void	print_meals(t_vars *vars, t_list *philo)
{
	pthread_mutex_lock(&vars->printf_m);
	printf("%d : meal eaten : %d\n", philo->philo_id, philo->meal_eaten);
	pthread_mutex_unlock(&vars->printf_m);
}

void	printf_action(t_vars *vars, int id, char *str)
{
	pthread_mutex_lock(&vars->printf_m);
	if (!vars->dieded)
	{
		printf("%d ms : ", (timestamp() - vars->first_timestamp));
		printf("%d ", id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&vars->printf_m);
}

int	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	time_diff(long long past, long long new)
{
	return (new - past);
}
