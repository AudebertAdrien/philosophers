/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:07:58 by motoko            #+#    #+#             */
/*   Updated: 2023/10/20 16:21:44 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printf_action(t_vars *vars, int id, char *str)
{
	pthread_mutex_lock(&vars->printf_m);	
	printf("%d ms ", (int)(timestamp() - vars->first_timestamp));
	printf("%d ", id);
	printf("%s\n", str);
	pthread_mutex_unlock(&vars->printf_m);	
}

long long	timestamp()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	time_diff(long long past, long long new)
{
	return (new - past);
}
