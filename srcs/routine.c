/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:55:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/15 13:52:30 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action(t_list *philo, char *str)
{
	struct timeval	tv;
	long long int	diff_time;
	gettimeofday(&tv, NULL);
	diff_time =  (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->start_t;
	printf("%lld ms %d is %s\n", diff_time, philo->philo_id, str);	
}

void	eating(t_vars *vars, t_list *philo)
{
//	action(philo, "BEFORE");

//	pthread_mutex_lock(&philo->fork_r);
//	pthread_mutex_lock(&philo->fork_l);

	pthread_mutex_lock(&(vars->fork_tab[philo->fork_r]));
	pthread_mutex_lock(&(vars->fork_tab[philo->fork_l]));

	//printf("ID %d TAKE fork\n",philo->philo_id);
//	printf("ID %d, MEAL %d\n",philo->philo_id, philo->meal_eaten);

	//action(philo, "eating");
	philo->meal_eaten += 1;

	//usleep(philo->vars->tt_e * 10);
	usleep(15000);

	pthread_mutex_unlock(&(vars->fork_tab[philo->fork_r]));
	pthread_mutex_unlock(&(vars->fork_tab[philo->fork_l]));

//	pthread_mutex_unlock(&philo->fork_r);
//	pthread_mutex_unlock(&philo->fork_l);

	//printf("ID %d DROP fork\n",philo->philo_id);
//	action(philo, "AFTER");
}

void	sleeping(t_list *philo)
{
	action(philo, "sleeping");
	//usleep(philo->vars->tt_s * 1000);
}

void	thinking(t_list *philo)
{
	action(philo, "thinking");
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
	printf("start_t : %lld\n" , phi->start_t);
	int	i = 0;
	if (phi->philo_id % 2 == 0)
		usleep(15000);
	while (i < 2)
	{
		usleep(15000);
		eating(vars, phi);
		//sleeping(phi);
		//thinking(phi);
		i++;
	}
}
