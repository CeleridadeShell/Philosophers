/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:26:54 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/05 00:21:19 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	set_timestamps(t_common_data *common_data)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
	{
		printf("Error geting time of day!\n");
		return ;
	}
	common_data->timestamp_init = current_time.tv_sec * 1000LL \
	+ current_time.tv_usec / 1000;
	common_data->timestamp_current = common_data->timestamp_init;
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
	pthread_mutex_lock(philo->common_data->time);
	philo->common_data->timestamp_current = current_time.tv_sec * 1000LL \
	+ current_time.tv_usec / 1000;
	return_time = philo->common_data->timestamp_current \
	- philo->common_data->timestamp_init;
	pthread_mutex_unlock(philo->common_data->time);
	return (return_time);
}
