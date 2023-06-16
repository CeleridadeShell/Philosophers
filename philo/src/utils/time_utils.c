/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:26:54 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/16 23:46:06 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	set_timestamps(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->common_data->get_time);
	if (gettimeofday(&current_time, NULL))
	{
		printf("Error geting time of day!\n");
		return ;
	}
	if (philo->common_data->timestamp_init == -1)
		philo->common_data->timestamp_init = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
	pthread_mutex_unlock(philo->common_data->get_time);
}

long long	get_current_timestamp(t_philo *philo)
{
	struct timeval	current_time;
	long long		return_time;

	if (gettimeofday(&current_time, NULL))
	{
		printf("Error geting time of day!\n");
		return (-1);
	}
	return_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) \
	- philo->common_data->timestamp_init;
	return (return_time);
}
