/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:31 by motoko            #+#    #+#             */
/*   Updated: 2023/10/03 19:09:26 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_list *philo)
{
	struct timeval	tv;
	long long int	diff_time;

	gettimeofday(&tv, NULL);
	diff_time =  (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->start_t;
	printf("%lld ms %d is thinking\n", diff_time, philo->philo_id);	
	sleep(2);
	eating(philo);
}

void	eating(t_list *philo)
{
	struct timeval	tv;
	long long int	diff_time;

	gettimeofday(&tv, NULL);
	diff_time =  (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->start_t;
	printf("%lld ms %d is eating\n", diff_time, philo->philo_id);	
	sleep(2);
	sleeping(philo);
}

void	sleeping(t_list *philo)
{
	struct timeval	tv;
	long long int	diff_time;

	gettimeofday(&tv, NULL);
	diff_time =  (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->start_t;
	printf("%lld ms %d is sleeping\n", diff_time, philo->philo_id);	
	sleep(2);
	//thinking(philo);
}

void	*routine(void *data)
{
	t_list		*philo;
	int		is_error;
	struct timeval	tv;
	long long int	start_t;

	gettimeofday(&tv, NULL);
	philo = (t_list *)data;

	pthread_mutex_lock(philo->fork_r);
	start_t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->start_t = start_t;
	printf("start_t : %lld\n" , philo->start_t);
	
	thinking(philo);
	pthread_mutex_unlock(philo->fork_r);
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

int	destroy_mutex(t_vars *vars)
{
	int	i;
	int	is_error;

	i = 0;
	while (i < vars->philo_nb)
	{
		is_error = pthread_mutex_destroy(vars->philo_lst[i].fork_r);
		if (is_error)
			handle_error("error : pthread_mutex_destroy\n");
		i++;
	}
	return (0);
}

int	assign_mutex(t_list *new)
{
	pthread_mutex_t	*fork_r;
	int		is_error;

	fork_r = malloc(sizeof(pthread_mutex_t));
	is_error = pthread_mutex_init(fork_r, NULL);
	if (is_error)
		handle_error("error : pthread_mutex_init\n");
	new->fork_r = fork_r;
	return (0);
}

int	create_tab(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->philo_nb)
	{
		vars->philo_lst[i].philo_id = i + 1;
		assign_mutex(&vars->philo_lst[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.philo_nb = 4;
	vars.philo_lst = ft_calloc(5, sizeof(t_list));
	create_tab(&vars);
	print_tab(&vars);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutex(&vars);
	free_forks(&vars);
	free(vars.philo_lst);
	vars.philo_lst = NULL;
	return (0);
}
