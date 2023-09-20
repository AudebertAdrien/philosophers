/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:51:27 by motoko            #+#    #+#             */
/*   Updated: 2023/09/20 14:08:26 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*my_turn(void *arg)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		sleep(1);
		printf("My turn %d\n", i);
		i++;
	}
}


void	your_turn(void)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		sleep(1);
		printf("Your turn %d\n", i);
		i++;
	}
}


int	main(int argc, char **argv)
{
	pthread_t	newthread;

	pthread_create(&newthread, NULL, my_turn, NULL);
	//my_turn();
	your_turn();
	return (0);
}
