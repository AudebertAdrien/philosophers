/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:55:45 by motoko            #+#    #+#             */
/*   Updated: 2023/10/08 15:59:32 by motoko           ###   ########.fr       */
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

int	eating(t_list *philo)
{
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(philo->fork_l);
	
	printf("id %d, meal %d\n",philo->philo_id, philo->meal_nb);
	if (philo->meal_nb == 0)
		return (0);
	action(philo, "eating");
	philo->meal_nb -= 1;

	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);

	usleep(TIME);
	return (0);
}

int	sleeping(t_list *philo)
{
	action(philo, "sleeping");
	usleep(TIME);
	return (0);
}

int	thinking(t_list *philo)
{
	action(philo, "thinking");
	usleep(TIME);
	return (0);
}

void	*routine(void *data)
{
	t_list		*philo;
	int		is_error;
	struct timeval	tv;
	long long int	start_t;

	philo = (t_list *)data;
	gettimeofday(&tv, NULL);

	start_t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->start_t = start_t;
	printf("start_t : %lld\n" , philo->start_t);
	
	eating(philo);
	sleeping(philo);
	thinking(philo);
}
