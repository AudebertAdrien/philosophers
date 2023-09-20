/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:51:27 by motoko            #+#    #+#             */
/*   Updated: 2023/09/20 19:03:25 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int balance = 0;

pthread_mutex_t mutex;

int	read_balance()
{
	usleep(250000);
	return (balance);	
}

void	write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

void	*deposite(void *amount)
{
	pthread_mutex_lock(&mutex);
	int account_balance = read_balance();

	account_balance += *((int *)amount);
	write_balance(account_balance);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	int	before = read_balance();
	printf("Before: %d\n", before);
	int credit1 = 300;
	int credit2 = 200;

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread1, NULL, deposite, (void *)&credit1);
	pthread_create(&thread2, NULL, deposite, (void *)&credit2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	int after = read_balance();
	printf("After: %d\n", after);

	return (0);
}

/*
void	*my_turn(void *arg)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		sleep(1);
		printf("My turn %d\n", i);
		i++;
	}
	return (NULL);
}


void	*your_turn(void *)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		sleep(1);
		printf("Your turn %d\n", i);
		i++;
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	pthread_t	new_thread1;
	pthread_t	new_thread2;

	pthread_create(&new_thread1, NULL, my_turn, NULL);
	pthread_join(new_thread1, NULL);
	//my_turn();

	pthread_create(&new_thread2, NULL, your_turn, NULL);
	pthread_join(new_thread2, NULL);
	//your_turn();
	return (0);
}
*/