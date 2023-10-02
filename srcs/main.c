/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:00:50 by motoko            #+#    #+#             */
/*   Updated: 2023/10/02 16:12:41 by motoko           ###   ########.fr       */
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

	/*
	struct timeval	tv;
	long long int	start_t;
	gettimeofday(&tv, NULL);
	start_t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("start_t : %lld\n" , start_t);
	printf("id %d, f_r %p : f_l %p\n" ,philo->philo_id, fork_r, fork_l);
	*/
	
void	*routine(void *lst)
{
	t_list		*philo;
	int		i;

	i = 0;
	philo = (t_list *)lst;

	pthread_mutex_lock(philo->fork_r);
	//pthread_mutex_lock(philo->fork_l);
	//pthread_mutex_lock(philo->next->fork_r);
	printf("philo id : %d\n", philo->philo_id);
	/*
	if (philo->philo_id == philo->vars->philo_nb)
		philo->fork_l = NULL;
	else
		philo->fork_l = philo->next->fork_r;
	*/
	pthread_mutex_unlock(philo->fork_r);
	//pthread_mutex_unlock(philo->fork_l);
	//pthread_mutex_unlock(philo->next->fork_r);


	/*
	while (i < philo->vars->meal_nb)
	{
		pthread_mutex_lock((philo)->fork_r);
		pthread_mutex_unlock((philo)->fork_r);
		i++;
	}
	*/
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
		pthread_mutex_destroy(lst->fork_r);
	//	pthread_mutex_destroy(lst->fork_l);
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
