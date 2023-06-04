/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/04 17:21:24 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int verify_end(t_philo * philo)
{
	if (philo->common_data->someone_died == 1)
		return (1);
	if (philo->common_data->opt_num_of_meals != -1 &&
	philo->meals_had > philo->common_data->opt_num_of_meals)
		return (1);
	return (0);
}

void 	*lonely_philo(t_philo *philo)
{
	printf("%lld Philosopher %d has taken a fork\n", get_current_timestamp(philo), (philo)->id + 1);
	usleep((philo)->common_data->time_to_die * 1000);
	printf("%lld Philosopher %d died.\n", \
			get_current_timestamp(philo), (philo)->id + 1);
	return (NULL);
}

void	*philo_life(void *philo_data)
{
	t_philo* philo;

	philo = (t_philo *)philo_data;
	if(philo->common_data->num_of_philos == 1)
		return(lonely_philo(philo));
	if(philo->id % 2 == 0)
		usleep(1000);
	while(verify_end(philo) == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
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
		philo->meals_had++;
		philo->last_meal = get_current_timestamp(philo);
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

void * monitor_life(void * data_monitor)
{
	t_philo **philos;
	int eats_count;
	int i;

	i = 0;
	eats_count = 0;
	philos = (t_philo **)data_monitor;
	if (philos[i]->common_data->num_of_philos == 1)
		return (NULL);
	while(1)
	{
		if (get_current_timestamp(philos[i]) - philos[i]->last_meal > \
		philos[i]->common_data->time_to_die)
		{

			while (eats_count < philos[i]->common_data->num_of_philos && philos[eats_count]->meals_had - 1 == philos[eats_count]->common_data->opt_num_of_meals) {
				eats_count++;
			}
			if (eats_count == philos[i]->common_data->num_of_philos && philos[i]->common_data->opt_num_of_meals != -1) {
				return (NULL);
			}
			philos[i]->common_data->someone_died = 1;
			pthread_mutex_lock(philos[i]->common_data->print);
			printf("%lld Philosopher %d died.\n", \
			get_current_timestamp(philos[i]), philos[i]->id + 1);
			pthread_mutex_unlock(philos[i]->common_data->print);
			return (NULL);
		}
		i++;
		if (i == philos[i]->common_data->num_of_philos - 1)
			i = 0;
	}
	return (NULL);
}

void	run_threads(t_common_data *common, pthread_t *philo_threads, \
t_philo **philos, pthread_t * monitor)
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

void	join_threads(t_common_data *common, pthread_t *philo_threads, pthread_t * monitor)
{
	int	i;

	i = 0;
	while (i < common->num_of_philos)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	pthread_join(*monitor, NULL);
}

void	run_life_cycle(t_common_data *common)
{
	pthread_t	*philo_threads;
	t_philo		**philos;
	pthread_t	monitor;

	philo_threads = (pthread_t *) malloc(sizeof(pthread_t) * common->num_of_philos);
	philos = (t_philo **) malloc(sizeof(t_philo *) * common->num_of_philos); //bug here?
	run_threads(common, philo_threads, philos, &monitor);
	join_threads(common, philo_threads, &monitor);
	free(philo_threads);
	free_philos(philos, common->num_of_philos);
}

int	main(int argc, char **argv)
{
	if (is_input_valid(argc, argv))
		run_life_cycle(convert_args(argv));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
