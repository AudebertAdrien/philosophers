/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:31 by motoko            #+#    #+#             */
/*   Updated: 2023/10/02 19:06:08 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *lst)
{
	t_list	*philo;

	philo = (t_list *)lst;
	pthread_mutex_lock(&(philo->fork_r));
	printf("philo %d\n", philo->philo_id);
	pthread_mutex_unlock(&(philo->fork_r));
}

pthread_t	create_threads(t_list **tab)
{
	int	is_error;
	int	i;

	i = 0;
	while (tab[i])
	{
		is_error = pthread_create(&(tab[i]->thread), NULL, &routine, (void *)tab[i]);
		if (is_error)
			handle_error("Error : pthread_create");
		i++;
	}
	return (0);
}

pthread_t	join_threads(t_list **tab)
{
	int	is_error;
	int	i;

	i = 0;
	while (tab[i])
	{
		is_error = pthread_join(tab[i]->thread, NULL);
		if (is_error)
			handle_error("Error : pthread_create");
		i++;
	}
	return (0);
}

int	assign_mutex(t_list *new)
{
	pthread_mutex_t	fork_r;
	int		is_error;

	is_error = pthread_mutex_init(&(new->fork_r), NULL);
	if (is_error)
		handle_error("error : pthread_mutex_init\n");
	return (0);
}

int	create_tab(t_list **tab, int size)
{
	t_list		*new;
	int		i;

	i = 0;
	while (i < size)
	{
		new = (t_list *)ft_calloc(1, sizeof(t_list));
		if (!new)
			return (0);
		new->philo_id = i + 1;
		new->meal_nb = 5;
		assign_mutex(tab[i]);
		tab[i] = new;
		i++;
	}
	tab[i] = NULL;
	return (0);
}

int	destroy_mutex(t_list **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		pthread_mutex_destroy(&(tab[i]->fork_r));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	**tab;

	tab = ft_calloc(5, sizeof(t_list));
	create_tab(tab, 4);
	//print_tab(tab);
	create_threads(tab);
	join_threads(tab);
	//destroy_mutex(tab);
	free_tab((void *)tab);
	return (0);
}
