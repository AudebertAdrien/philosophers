/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:01 by motoko            #+#    #+#             */
/*   Updated: 2023/10/03 18:48:49 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

typedef struct s_vars t_vars;

typedef struct s_list
{
	int		philo_id;
	pthread_t	thread;	
	pthread_mutex_t	*fork_r;
	long long int	start_t;
}	t_list;

struct s_vars
{
	int		philo_nb;
	int		meal_nb;
	t_list		*philo_lst;
};

void	print_tab(t_vars *vars);
void	handle_error(char *msg);
void	free_forks(t_vars *vars);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

void	thinking(t_list *philo);
void	eating(t_list *philo);
void	sleeping(t_list *philo);
#endif

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died
//#define time_msg(msg) ft_putstr(msg)
