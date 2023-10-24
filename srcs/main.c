/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:31 by motoko            #+#    #+#             */
/*   Updated: 2023/10/24 14:49:06 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_value(t_vars *vars, int *param, char *arg)
{
	*param = ft_atoi(vars, arg);
}

int	init_data(t_vars *vars,int argc, char **argv)
{
	void	(*func)(t_vars *, int *, char *) = assign_value;

	if (argc != 5 && argc != 6)
		return (handle_error("Error : Not enough arguments\n Should be 4 or 5"));
	vars->error = 0;
	vars->dieded = 0;
	func(vars, &vars->philo_nb, argv[1]);
	func(vars, &vars->tt_d, argv[2]);
	func(vars, &vars->tt_e, argv[3]);
	func(vars, &vars->tt_s, argv[4]);
	if (argc == 6)
		func(vars, &vars->meal_count, argv[5]);
	else
		vars->meal_count = 0;
	vars->philo_lst = ft_calloc(vars->philo_nb, sizeof(t_list));
	if (vars->error == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (check_args(&vars, argv))
		return (0);
	if (init_data(&vars, argc, argv))
		return (0);
	create_mutex_tab(&vars);
	create_tab(&vars);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutex(&vars);
	free_data(&vars);
	return (0);
}
