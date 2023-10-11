/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:17:56 by motoko            #+#    #+#             */
/*   Updated: 2023/10/11 16:07:51 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_valid_number(t_vars *vars, char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i])
	{
		if (i > 0 && nptr[i] == '-')
		{
			vars->bad_arg = nptr;
			return (1);
		}
		i++;
	}
	return (0);
}
