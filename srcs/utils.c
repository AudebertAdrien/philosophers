/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:58 by motoko            #+#    #+#             */
/*   Updated: 2023/10/02 17:46:02 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_tab(t_list **tab)
{
	int	i;
	i = 0;
	while (tab[i])
	{
		printf("id %d\n", tab[i]->philo_id);
		i++;
	}
}

void	free_tab(void **tab)
{
	int	i;

	if (!tab)
		return ;
	if (!*tab)
	{
		free(tab);
		tab = NULL;
		return ;
	}
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	handle_error(char *msg)
{
	ft_putstr(msg);
	exit(EXIT_FAILURE);
}
