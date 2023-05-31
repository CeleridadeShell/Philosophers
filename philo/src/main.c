/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/31 03:05:44 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philo_life(void *philo)
{
	set_timestamps((t_philo *)philo);
	printf("%lld Philosopher %d is eating.\n", ((t_philo *)philo)->timestamp_current - ((t_philo *)philo)->timestamp_init, ((t_philo *)philo)->id);
	set_timestamps((t_philo *)philo);
	printf("%lld Philosopher %d is sleeping.\n", ((t_philo *)philo)->timestamp_current - ((t_philo *)philo)->timestamp_init, ((t_philo *)philo)->id);
	set_timestamps((t_philo *)philo);
	printf("%lld Philosopher %d is thinking.\n", ((t_philo *)philo)->timestamp_current - ((t_philo *)philo)->timestamp_init, ((t_philo *)philo)->id);
	return (NULL);
}

void	run_life_cycle(t_common_data common)
{
	int			i;
	pthread_t	*philo_threads;
	t_philo		**philos;

	i = 0;
	philo_threads = (pthread_t *) malloc(sizeof(pthread_t) * common.num_of_philos);
	philos = (t_philo **) malloc(sizeof(t_philo *) * common.num_of_philos); //maybe here?
	
	while (i < common.num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		initialize_philo(philos[i], &common, i);
		
		if (pthread_create(&philo_threads[i], NULL, &philo_life, (void *) philos[i]))
		{
			printf("Error creating thread!\n");
			free(philo_threads);
			free_philos(philos, common.num_of_philos);
			return ;
		}
		
		i++;
	}
	
	i = 0;

	while (i < common.num_of_philos)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	free(philo_threads);
	free_philos(philos, common.num_of_philos);
}

int	main(int argc, char **argv)
{	
	if (is_input_valid(argc, argv))
	{
		run_life_cycle(convert_args(argv));
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
