/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 23:52:19 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/17 00:20:57 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	prints(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->common_data->print);
	if (action == FORK)
		printf("%lld Philosopher %d has taken a fork.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
	else if (action == EAT)
		printf("%lld Philosopher %d is eating.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
	else if (action == SLEEP)
		printf("%lld Philosopher %d is sleeping.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
	else if (action == THINK)
		printf("%lld Philosopher %d is thinking.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
	else if (action == DIE)
		printf("%lld Philosopher %d died.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
	else
		printf("Invalid action.\n");
	pthread_mutex_unlock(philo->common_data->print);
}
