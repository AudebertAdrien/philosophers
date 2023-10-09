/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:31 by motoko            #+#    #+#             */
/*   Updated: 2023/10/09 15:16:16 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars.philo_nb = 5;
	vars.philo_lst = ft_calloc(5, sizeof(t_list));
	create_mutex_tab(&vars);
	create_tab(&vars);
	print_tab(&vars);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutex(&vars);
	free_data(&vars);
	return (0);
}
