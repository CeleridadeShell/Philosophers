/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:03:48 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/17 01:48:37 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	verify_end(t_philo *philo)
{
	pthread_mutex_lock(philo->common_data->dead_or_alive_mutex);
	if (philo->common_data->someone_died == 1 || philo->meals_had == \
	philo->common_data->opt_num_of_meals)
	{
		pthread_mutex_unlock(philo->common_data->dead_or_alive_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->common_data->dead_or_alive_mutex);
	return (0);
}

int	create_philos_threads(t_common_data *common, pthread_t *philo_threads, \
t_philo **philos)
{
	int	i;

	i = 0;
	while (i < common->num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		initialize_philo(philos[i], common, i);
		if (pthread_create(&philo_threads[i], NULL, &philo_life, \
		(void *) philos[i]))
		{
			printf("Error creating thread!\n");
			free(philo_threads);
			free_philos(philos, common->num_of_philos);
			return (0);
		}	
		i++;
	}
	return (1);
}

void	run_threads(t_common_data *common, pthread_t *philo_threads, \
t_philo **philos)
{
	pthread_t	monitor;
	int			i;

	if (create_philos_threads(common, philo_threads, philos) == 0)
		return ;
	pthread_create(&monitor, NULL, &monitor_thread, (void *) philos);
	i = 0;
	while (i < common->num_of_philos)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
