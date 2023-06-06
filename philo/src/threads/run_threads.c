/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 01:09:40 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/06 23:44:49 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	verify_end(t_philo *philo)
{
	pthread_mutex_lock(philo->common_data->dead_or_alive);
	if (philo->common_data->someone_died == 1)
	{
		pthread_mutex_unlock(philo->common_data->dead_or_alive);
		return (1);
	}
	pthread_mutex_unlock(philo->common_data->dead_or_alive);
	pthread_mutex_lock(philo->common_data->meals_had_mutex);
	if (philo->common_data->opt_num_of_meals != -1 \
	&& philo->meals_had > philo->common_data->opt_num_of_meals)
	{
		pthread_mutex_unlock(philo->common_data->meals_had_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->common_data->meals_had_mutex);
	return (0);
}

static void	*lonely_philo(t_philo *philo)
{
	printf("%lld Philosopher %d has taken a fork\n", \
	get_current_timestamp(philo), (philo)->id + 1);
	usleep((philo)->common_data->time_to_die * 1000);
	printf("%lld Philosopher %d died.\n", \
	get_current_timestamp(philo), (philo)->id + 1);
	return (NULL);
}

static void	*philo_life(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->common_data->num_of_philos == 1)
		return (lonely_philo(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (verify_end(philo) == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (verify_end(philo) == 1)
			break ;
		pthread_mutex_lock(philo->common_data->print);
		printf("%lld Philosopher %d has taken a fork.\n", get_current_timestamp(philo), (philo)->id + 1);
		pthread_mutex_unlock(philo->common_data->print);
		
		pthread_mutex_lock(philo->right_fork);
		if (verify_end(philo) == 1)
			break ;
		pthread_mutex_lock(philo->common_data->print);
		printf("%lld Philosopher %d has taken a fork.\n", get_current_timestamp(philo), (philo)->id + 1);
		pthread_mutex_unlock(philo->common_data->print);
		
		if (verify_end(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		
		pthread_mutex_lock(philo->common_data->print);
		printf("%lld Philosopher %d is eating.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
		pthread_mutex_unlock(philo->common_data->print);
		usleep((philo)->common_data->time_to_eat * 1000);
		
		pthread_mutex_lock(philo->common_data->meals_had_mutex);
		philo->meals_had++;
		pthread_mutex_unlock(philo->common_data->meals_had_mutex);
		
		pthread_mutex_lock(philo->common_data->last_meal_mutex);
		philo->last_meal = get_current_timestamp(philo);
		pthread_mutex_unlock(philo->common_data->last_meal_mutex);
		
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		if (verify_end(philo) == 1)
			break ;
		pthread_mutex_lock(philo->common_data->print);
		printf("%lld Philosopher %d is sleeping.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
		pthread_mutex_unlock(philo->common_data->print);
		usleep((philo)->common_data->time_to_sleep * 1000);
		
		if (verify_end(philo) == 1)
			break ;
		pthread_mutex_lock(philo->common_data->print);
		printf("%lld Philosopher %d is thinking.\n", \
		get_current_timestamp(philo), (philo)->id + 1);
		pthread_mutex_unlock(philo->common_data->print);
	}
	return (NULL);
}

static void	*monitor_life(void *data_monitor)
{
	t_philo	**philos;
	int		eats_count;
	int		i;

	i = 0;
	eats_count = 0;
	philos = (t_philo **)data_monitor;
	if (philos[i]->common_data->num_of_philos == 1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(philos[i]->common_data->last_meal_mutex);
		if (get_current_timestamp(philos[i]) - philos[i]->last_meal > \
		philos[i]->common_data->time_to_die)
		{
			pthread_mutex_unlock(philos[i]->common_data->last_meal_mutex);
			pthread_mutex_lock(philos[i]->common_data->meals_had_mutex);
			while (eats_count < philos[i]->common_data->num_of_philos \
			&& philos[eats_count]->meals_had - 1 \
			== philos[eats_count]->common_data->opt_num_of_meals)
			{
				pthread_mutex_unlock(philos[i]->common_data->meals_had_mutex);
				eats_count++;
			}
			pthread_mutex_unlock(philos[i]->common_data->meals_had_mutex);
			if (eats_count == philos[i]->common_data->num_of_philos \
			&& philos[i]->common_data->opt_num_of_meals != -1)
			{
				return (NULL);
			}
			pthread_mutex_lock(philos[i]->common_data->dead_or_alive);
			philos[i]->common_data->someone_died = 1;
			pthread_mutex_unlock(philos[i]->common_data->dead_or_alive);
			pthread_mutex_lock(philos[i]->common_data->print);
			printf("%lld Philosopher %d died.\n", \
			get_current_timestamp(philos[i]), philos[i]->id + 1);
			pthread_mutex_unlock(philos[i]->common_data->print);
			return (NULL);
		}
		pthread_mutex_unlock(philos[i]->common_data->last_meal_mutex);
		i++;
		if (i == philos[i]->common_data->num_of_philos - 1)
			i = 0;
	}
	return (NULL);
}

void	run_threads(t_common_data *common, pthread_t *philo_threads, \
t_philo **philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	set_timestamps(common);
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
			return ;
		}
		i++;
	}
	pthread_create(monitor, NULL, &monitor_life, (void *) philos);
}
