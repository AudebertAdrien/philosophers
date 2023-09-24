/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:01 by motoko            #+#    #+#             */
/*   Updated: 2023/09/24 18:04:28 by motoko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died

//#define time_msg(msg) ft_putstr(msg)

typedef struct s_list
{
	int		id;	
	pthread_t	thread;	
	pthread_mutex_t	*mutex;
	struct s_list	*next;
}	t_list;

void	print_lst(t_list *lst);	
void	handle_error(char *msg);
t_list	*ft_lstnew(int id);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

#endif
