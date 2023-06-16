/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:31:42 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/17 00:32:06 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	single_philo(t_philo *philo)
{
	if (philo->common_data->num_of_philos == 1)
	{
		prints(philo, FORK);
		usleep(philo->common_data->time_to_die * 1000);
		prints(philo, DIE);
		return (1);
	}
	return (0);
}

static void	while_life_2(t_philo *philo)
{
	prints(philo, FORK);
	prints(philo, FORK);
	prints(philo, EAT);
	usleep((philo)->common_data->time_to_eat * 1000);
	pthread_mutex_lock(philo->common_data->dead_or_alive_mutex);
	philo->last_meal = get_current_timestamp(philo);
	philo->meals_had++;
	pthread_mutex_unlock(philo->common_data->dead_or_alive_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	while_life(t_philo *philo)
{
	while (verify_end(philo) == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if (verify_end(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		while_life_2(philo);
		if (verify_end(philo))
			break ;
		prints(philo, SLEEP);
		usleep((philo)->common_data->time_to_sleep * 1000);
		if (verify_end(philo))
			break ;
		prints(philo, THINK);
		usleep(1000);
	}
}

void	*philo_life(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *) philo_data;
	set_timestamps(philo);
	if (single_philo(philo) == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		usleep(1400);
	while_life(philo);
	return (NULL);
}
