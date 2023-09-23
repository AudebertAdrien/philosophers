/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:00:50 by motoko            #+#    #+#             */
/*   Updated: 2023/09/23 21:07:53 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

pthread_mutex_t mutex;
int	email = 0;

void	*my_turn(void *lst)
{
	int	id;

	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 5; i++)
		email++;
	pthread_mutex_unlock(&mutex);
	//printf("email : %d\n", email);
	/*
	id = ((t_list *)lst)->id;
	if (id % 2 == 0)
		printf("odd => %d\n", (((t_list *)lst)->id));
	else 
		printf("even => %d\n", (((t_list *)lst)->id));
	*/
}

pthread_t	create_threads(t_list *lst)
{
	int		is_error;

	while (lst)
	{
		is_error = pthread_create(&(lst->thread), NULL, &my_turn, (void *)lst);
		if (is_error)
		{
			printf("error create : %d\n", is_error);
			return (0);
		}
		lst = lst->next;
	}
	return (0);
}


pthread_t	join_threads(t_list *lst)
{
	int		is_error;

	while (lst)	
	{
		is_error = pthread_join(lst->thread, NULL);
		if (is_error)
		{
			printf("error join : %d\n", is_error);
			return (0);
		}
		lst = lst->next;
	}	
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*new;
	int	i;
	int		is_error;

	pthread_mutex_init(&mutex, NULL);
	i = 1;
	while (argv[i])
	{
		new = ft_lstnew(i);
		ft_lstadd_back(&lst, new);
		i++;
	}
	print_lst(lst);
	create_threads(lst);
	join_threads(lst);

	pthread_mutex_destroy(&mutex);
	printf("email : %d\n", email);
	return (0);
}
