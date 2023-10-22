/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:01 by motoko            #+#    #+#             */
/*   Updated: 2023/10/22 19:18:40 by motoko           ###   ########.fr       */
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
	int		fork_r;
	int		fork_l;
	int		last_meal;
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
	int		dieded;
	int		error;
	int		first_timestamp;
	char		*bad_arg;
	pthread_mutex_t	*fork_tab;
	pthread_mutex_t	printf_m;
	pthread_mutex_t	check_death;
	t_list		*philo_lst;
};

int	timestamp(void);
int	time_diff(long long past, long long new);
int	is_dead(t_vars *vars);

int	check_args(t_vars *vars, char **argv);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
int	ft_atoi(t_vars *vars, const char *nptr);
void	ft_putstr(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

void	printf_action(t_vars *vars, int id, char *str);
void	print_tab(t_vars *vars);

int	handle_error(char *msg);
int	destroy_mutex(t_vars *vars);
int	free_data(t_vars *vars);

int	create_tab(t_vars *vars);
int	create_mutex_tab(t_vars *vars);
int	create_threads(t_vars *vars);
int	join_threads(t_vars *vars);

void	*routine(void *data);
void	action(t_list *philo, char *str);
int	eating(t_vars *vars, t_list *philo);
int	sleeping(t_vars *vars, t_list *philo);
int	thinking(t_vars *vars, t_list *philo);
#endif
