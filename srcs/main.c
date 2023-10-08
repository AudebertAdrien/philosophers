/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:31 by motoko            #+#    #+#             */
/*   Updated: 2023/10/08 15:45:00 by motoko           ###   ########.fr       */
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

pthread_t	create_threads(t_vars *vars)
{
	int	is_error;
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		is_error = pthread_create(&(vars->philo_lst[i]).thread,
				NULL, &routine, &vars->philo_lst[i]);
		if (is_error)
			handle_error("error : pthread_create");
		i++;
	}
	return (0);
}

pthread_t	join_threads(t_vars *vars)
{
	int	is_error;
	int	i;

	i = 0;
	while (i < vars->philo_nb)
	{
		is_error = pthread_join(vars->philo_lst[i].thread, NULL);
		if (is_error)
			handle_error("error : pthread_create");
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.philo_nb = 4;
	vars.philo_lst = ft_calloc(5, sizeof(t_list));
	create_mutex_tab(&vars);
	create_tab(&vars);
	print_tab(&vars);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutex(&vars);
	free(vars.fork_tab);
	vars.fork_tab = NULL;
	return (0);
}
