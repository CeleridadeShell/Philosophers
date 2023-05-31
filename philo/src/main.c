/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/31 23:02:09 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philo_life(void *philo)
{
	set_timestamps((t_philo *)philo);
	printf("%lld Philosopher %d is eating.\n", \
	get_current_timestamp((t_philo *)philo), ((t_philo *)philo)->id + 1);
	usleep(((t_philo *)philo)->common_data->time_to_eat * 1000);
	printf("%lld Philosopher %d is sleeping.\n", \
	get_current_timestamp((t_philo *)philo), ((t_philo *)philo)->id + 1);
	usleep(((t_philo *)philo)->common_data->time_to_sleep * 1000);
	printf("%lld Philosopher %d is thinking.\n", \
	get_current_timestamp((t_philo *)philo), ((t_philo *)philo)->id + 1);
	return (NULL);
}

void	run_threads(t_common_data common, pthread_t *philo_threads, \
t_philo **philos)
{
	int	i;

	i = 0;
	while (i < common.num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		initialize_philo(philos[i], &common, i);
		if (pthread_create(&philo_threads[i], NULL, &philo_life, \
		(void *) philos[i]))
		{
			printf("Error creating thread!\n");
			free(philo_threads);
			free_philos(philos, common.num_of_philos);
			return ;
		}	
		i++;
	}	
}

void	join_threads(t_common_data common, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < common.num_of_philos)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
}

void	run_life_cycle(t_common_data common)
{
	pthread_t	*philo_threads;
	t_philo		**philos;

	philo_threads = (pthread_t *) malloc(sizeof(pthread_t) * common.num_of_philos);
	philos = (t_philo **) malloc(sizeof(t_philo *) * common.num_of_philos); //bug here?
	run_threads(common, philo_threads, philos);
	join_threads(common, philo_threads);
	free(philo_threads);
	free_philos(philos, common.num_of_philos);
}

int	main(int argc, char **argv)
{	
	if (is_input_valid(argc, argv))
		run_life_cycle(convert_args(argv));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
