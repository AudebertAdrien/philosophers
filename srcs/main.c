/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:00:50 by motoko            #+#    #+#             */
/*   Updated: 2023/09/27 17:14:45 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	/*
		if (!(philo_id % 2 == 0) && switch_stat)
		{
			printf("%d stat even => %s\n", philo_id, stat);
			stat = "SLEEP";
			printf("%d stat even => %s\n", philo_id, stat);
			switch_stat = 0;
		}
		else 
		{
			printf("%d stat odd => %s\n", philo_id, stat);
			stat = "EAT";
			printf("%d stat odd => %s\n", philo_id, stat);
			switch_stat = 1;
		}
		*/


#include <philosophers.h>

void	*routine(void *lst)
{
	pthread_mutex_t	*mutex;	
	int		philo_id;
	int		meal_nb;
	time_t		sec;
	suseconds_t	usec;
	suseconds_t	diff_time;
	char		*stat;
	int i = 0;
	int switch_stat = 1;

	philo_id = ((t_list *)lst)->philo_id;
	stat = ((t_list *)lst)->stat;
	meal_nb = ((t_list *)lst)->meal_nb;
	mutex = ((t_list *)lst)->mutex;

	usec = ((t_list *)lst)->usec;

	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	diff_time = tv.tv_usec;
	printf("%d diff time %ld\n", philo_id, diff_time);
	while (i < meal_nb)
	{
		pthread_mutex_lock(mutex);

		printf("v1 : %d stat even => %s\n", philo_id, stat);
		if (!strcmp(stat, "SLEEP"))
			stat = "EAT";
		else if (!strcmp(stat, "EAT"))
			stat = "SLEEP";
		else 
			printf("AAA");
		printf("v2 : %d stat even => %s\n", philo_id, stat);
			pthread_mutex_unlock(mutex);
		i++;
	}
	return (NULL);
}

pthread_t	create_threads(t_list *lst)
{
	int		is_error;

	while (lst)
	{
		is_error = pthread_create(&(lst->thread_id), NULL, &routine, (void *)lst);
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
		is_error = pthread_join(lst->thread_id, NULL);
		if (is_error)
			handle_error("pthread_join");
		lst = lst->next;
	}	
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*new;
	int	i;
	int	is_error;

	struct timeval tv;


	is_error = gettimeofday(&tv, NULL);
	printf("gettineofday %d\n", is_error);
	printf("tv_usec %ld\n", tv.tv_usec);

	pthread_mutex_t mutex;
	is_error = pthread_mutex_init(&mutex, NULL);
	if (is_error)
		handle_error("pthread_init");
	i = 1;
	while (argv[i])
	{
		new = ft_lstnew(i);
		new->mutex = &mutex;
		new->usec = tv.tv_usec;
		new->meal_nb = 1;
		if (!(new->philo_id % 2 == 0))
		{
			printf("id => %d\n", new->philo_id);
			new->stat = "EAT";
		}
		else 
		{
			printf("id => %d\n", new->philo_id);
			new->stat = "SLEEP";
		}
		ft_lstadd_back(&lst, new);
		i++;
	}
	lst->next->meal_nb = 3;
	//print_lst(lst);
	create_threads(lst);
	join_threads(lst);
	pthread_mutex_destroy(&mutex);
	return (0);
}
