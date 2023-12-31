/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:17:56 by motoko            #+#    #+#             */
/*   Updated: 2023/10/29 19:39:09 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_valid_number(t_vars *vars, char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (1);
		if (nptr[i] == '-')
		{
			vars->bad_arg = nptr;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_args(t_vars *vars, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_number(vars, argv[i]))
			return (handle_error("Error : Not a valid number"));
		i++;
	}
	return (0);
}
