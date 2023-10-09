/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:01 by motoko            #+#    #+#             */
/*   Updated: 2023/10/09 15:41:03 by motoko           ###   ########.fr       */
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

#define	TIME_EAT 500000
#define	TIME_SLEEP 3000

typedef struct s_vars t_vars;

typedef struct s_list
{
	int		philo_id;
	pthread_t	thread;	
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	long long int	start_t;
	int		meal_nb;
	t_vars		*vars;
}	t_list;

struct s_vars
{
	int		philo_nb;
	pthread_mutex_t	*fork_tab;
	t_list		*philo_lst;
};

void	ft_putstr(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

void	print_tab(t_vars *vars);

void	handle_error(char *msg);
int	destroy_mutex(t_vars *vars);
int	free_data(t_vars *vars);

int	create_tab(t_vars *vars);
int	create_mutex_tab(t_vars *vars);
pthread_t	create_threads(t_vars *vars);
pthread_t	join_threads(t_vars *vars);

void	*routine(void *data);
void	action(t_list *philo, char *str);
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
