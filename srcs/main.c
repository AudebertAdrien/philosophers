/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:00:50 by motoko            #+#    #+#             */
/*   Updated: 2023/09/24 18:00:02 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	routine(void *lst)
{
	int		id;

	id = ((t_list *)lst)->id;
	if (id % 2 == 0)
		printf("odd => %d\n", id);
	else 
		printf("even => %d\n", id);
}

void	*init(void *lst)
{
	pthread_mutex_t	*mutex;	

	mutex = ((t_list *)lst)->mutex;
	pthread_mutex_lock(mutex);
	routine(lst);
	pthread_mutex_unlock(mutex);
	return (NULL);
}

pthread_t	create_threads(t_list *lst)
{
	int		is_error;

	while (lst)
	{
		is_error = pthread_create(&(lst->thread), NULL, &init, (void *)lst);
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

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*new;
	int	i;
	int	is_error;

	pthread_mutex_t mutex;
	is_error = pthread_mutex_init(&mutex, NULL);
	if (is_error)
		handle_error("pthread_init");
	i = 1;
	while (argv[i])
	{
		new = ft_lstnew(i);
		new->mutex = &mutex;
		ft_lstadd_back(&lst, new);
		i++;
	}
	print_lst(lst);
	create_threads(lst);
	join_threads(lst);
	pthread_mutex_destroy(&mutex);
	return (0);
}
