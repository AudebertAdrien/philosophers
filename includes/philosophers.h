/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:01 by motoko            #+#    #+#             */
/*   Updated: 2023/10/01 16:56:57 by motoko           ###   ########.fr       */
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

typedef struct s_list
{
	int		philo_id;
	pthread_t	thread;	
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;

	long long int	start_t;
	struct s_list	*next;
}	t_list;

typedef struct s_vars
{
	int		meal_nb;
	int		philo_nb;

	t_list		*philo_lst;	
}	t_vars;

//void	print_lst(t_list *lst);	
void	handle_error(char *msg);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

t_list	*ft_lstnew(int id);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
#endif

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died
//#define time_msg(msg) ft_putstr(msg)