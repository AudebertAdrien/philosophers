/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:01 by motoko            #+#    #+#             */
/*   Updated: 2023/10/12 15:21:31 by motoko           ###   ########.fr       */
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
	int		meal_eaten;
	t_vars		*vars;
}	t_list;

struct s_vars
{
	int		philo_nb;
	int		tt_d;
	int		tt_e;
	int		tt_s;
	int		meal_count;
	int		error;
	char		*bad_arg;
	pthread_mutex_t	*fork_tab;
	t_list		*philo_lst;
};

int	check_args(t_vars *vars, char **argv);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
int	ft_atoi(t_vars *vars, const char *nptr);
void	ft_putstr(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

void	print_tab(t_vars *vars);

int	handle_error(char *msg, char *arg);
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
