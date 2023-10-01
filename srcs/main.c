/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:00:50 by motoko            #+#    #+#             */
/*   Updated: 2023/10/01 18:29:38 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

	/*
		//printf("v1 : %d stat even => %s\n", philo_id, stat);
		if (!strcmp(stat, "SLEEP"))
		{
			stat = "EAT";
			sleep(5);
			gettimeofday(&tv, NULL);
			diff_time =  start_t - (tv.tv_sec * 1000 + tv.tv_usec / 1000);
			printf("diff time : %d\n", diff_time);
		}
		else if (!strcmp(stat, "EAT"))
		{
			stat = "SLEEP";
			//usleep(2000);
			//diff_time =  start_t - (tv.tv_sec * 1000 + tv.tv_usec / 1000);
			//printf("diff time : %d\n", diff_time);
		}
		else 
			printf("AAA");
		//printf("v2 : %d stat even => %s\n", philo_id, stat);
		*/

		//if (!(new->philo_id % 2 == 0))

void	*routine(void *lst)
{
	pthread_mutex_t	*fork_r;	
	pthread_mutex_t	*fork_l;	
	int		philo_id;
	int 		i;
	int 		switch_stat;
	int		diff_time;
	long long int	start_t;
	struct timeval	tv;

	i = 0;
	switch_stat = 1;

	t_list		*philo;
	int		meal_nb;

	philo = (t_list *)lst;
	meal_nb = philo->vars->meal_nb;

	printf("nb %d\n", meal_nb);

	philo_id = ((t_list *)lst)->philo_id;
	fork_r = &((t_list *)lst)->fork_r;
	if (philo_id == philo->vars->philo_nb)
		fork_l = NULL;
	else
		fork_l = &((t_list *)lst)->next->fork_r;
	

	gettimeofday(&tv, NULL);
	start_t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("start_t : %lld\n" , start_t);
	printf("id %d, f_r %p : f_l %p\n" ,philo_id, fork_r, fork_l);

	while (i < meal_nb)
	{
		pthread_mutex_lock(fork_r);
		pthread_mutex_unlock(fork_r);
		i++;
	}
	return (NULL);
}

pthread_t	create_threads(t_vars *vars)
{
	t_list		*lst;
	int		is_error;

	lst = vars->philo_lst;
	while (lst)
	{
		is_error = pthread_create(&(lst->thread), NULL, &routine, (void *)lst);
		if (is_error)
			handle_error("Error : pthread_create");
		lst = lst->next;
	}
	return (0);
}

pthread_t	join_threads(t_vars *vars)
{
	t_list	*lst;
	int	is_error;

	lst = vars->philo_lst;
	while (lst)
	{
		is_error = pthread_join(lst->thread, NULL);
		if (is_error)
			handle_error("Error : pthread_join");
		lst = lst->next;
	}	
	return (0);
}

int	destroy_mutex(t_vars *vars)
{
	t_list	*lst;

	lst = vars->philo_lst;
	while (lst)
	{
		pthread_mutex_destroy(&(lst->fork_r));
		pthread_mutex_destroy(&(lst->fork_l));
		lst = lst->next;
	}
	return (0);
}

int	create_lst(t_vars *vars, int argc, char **argv)
{
	t_list		*new;
	int		i;

	i = 1;
	vars->philo_lst = NULL;
	while (argv[i])
	{
		new = ft_lstnew(i);
		new->vars = vars;
		ft_lstadd_back(&(vars->philo_lst), new);
		i++;
	}
	return (0);
}

void	print_lst(t_vars *vars)
{
	t_list	*lst;
	
	lst = vars->philo_lst;
	while (lst)
	{
		printf("id %d\n", lst->philo_id);
		lst = lst->next;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.meal_nb = 3;
	vars.philo_nb = argc - 1;
	create_lst(&vars, argc, argv);
	print_lst(&vars);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutex(&vars);
	ft_lstclear(&(vars.philo_lst));
	return (0);
}
