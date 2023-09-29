/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:00:50 by motoko            #+#    #+#             */
/*   Updated: 2023/09/29 17:53:28 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*routine(void *lst)
{
	pthread_mutex_t	*fork;	
	int		philo_id;
	int		meal_nb;
	char		*stat;
	int 		i;
	int 		switch_stat;
	int		diff_time;
	long long int	start_t;
	struct timeval	tv;

	switch_stat = 1;
	i = 0;
	philo_id = ((t_list *)lst)->philo_id;
	stat = ((t_list *)lst)->stat;
	meal_nb = ((t_list *)lst)->meal_nb;
	fork = &((t_list *)lst)->fork;
	start_t = ((t_list *)lst)->start_t;

	gettimeofday(&tv, NULL);
	printf("start_t : %ld\n", tv.tv_usec + tv.tv_usec / 1000);
	((t_list *)lst)->start_t = tv.tv_usec + tv.tv_usec / 1000;
	diff_time =  start_t - (tv.tv_usec + tv.tv_usec / 1000);
	while (i < meal_nb)
	{
		pthread_mutex_lock(fork);
		printf("v1 : %d stat even => %s\n", philo_id, stat);
		if (!strcmp(stat, "SLEEP"))
			stat = "EAT";
		else if (!strcmp(stat, "EAT"))
			stat = "SLEEP";
		else 
			printf("AAA");
		printf("v2 : %d stat even => %s\n", philo_id, stat);
		pthread_mutex_unlock(fork);
		i++;
	}
	return (NULL);
}

pthread_t	create_threads(t_list *lst)
{
	int		is_error;

	while (lst)
	{
		is_error = pthread_create(&(lst->thread), NULL, &routine, (void *)lst);
		if (is_error)
			handle_error("pthread_create");
		lst = lst->next;
	}
	return (0);
}

pthread_t	join_threads(t_list *lst)
{
	int	is_error;

	while (lst)
	{
		is_error = pthread_join(lst->thread, NULL);
		if (is_error)
			handle_error("pthread_join");
		lst = lst->next;
	}	
	return (0);
}

int	destroy_mutex(t_list *lst)
{
	while (lst)
	{
		pthread_mutex_destroy(&(lst->fork));
		lst = lst->next;
	}
	return (0);
}

int	create_lst(t_list **lst, int argc, char **argv)
{
	t_list		*new;
	int		i;

	i = 1;
	while (argv[i])
	{
		new = ft_lstnew(i);
		new->meal_nb = 1;
		new->start_t = 0;
		if (!(new->philo_id % 2 == 0))
			new->stat = "EAT";
		else 
			new->stat = "SLEEP";
		ft_lstadd_back(lst, new);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*lst;

	lst = NULL;
	create_lst(&lst, argc, argv);
	print_lst(lst);
	create_threads(lst);
	join_threads(lst);
	destroy_mutex(lst);
	ft_lstclear(&lst);
	return (0);
}
