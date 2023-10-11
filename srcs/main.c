/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:31 by motoko            #+#    #+#             */
/*   Updated: 2023/10/11 17:26:21 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_vars *vars,int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	
	vars->error = 0;
	vars->philo_nb = 5;
	vars->philo_lst = ft_calloc(5, sizeof(t_list));
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (is_valid_number(&vars, "-23"))
		return (handle_error("Error : Not a valid number", vars.bad_arg));

	printf("atoi : %d\n", ft_atoi(&vars, "2147483649"));
	if (vars.error == 1)
	{
		printf("ERROR\n");
		return (0);
	}

	if (init_data(&vars, argc, argv))
		return (0);
	create_mutex_tab(&vars);
	create_tab(&vars);
	print_tab(&vars);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutex(&vars);
	free_data(&vars);
	return (0);
}
