/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:26:54 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/31 03:05:04 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	set_timestamps(t_philo *philo)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
	{
		printf("Error geting time of day!\n");
		return ;
	}
	if (philo->timestamp_init == -1)
		philo->timestamp_init = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
	if (philo->timestamp_current == -1)
		philo->timestamp_current = philo->timestamp_init;
	else
		philo->timestamp_current = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
}
