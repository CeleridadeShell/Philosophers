/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/05 01:13:14 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	join_threads(t_common_data *common, pthread_t *philo_threads, \
pthread_t *monitor)
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

static void	run_life_cycle(t_common_data *common)
{
	pthread_t	*philo_threads;
	t_philo		**philos;
	pthread_t	monitor;

	philo_threads = (pthread_t *) malloc(sizeof(pthread_t) \
		* common->num_of_philos);
	philos = (t_philo **) malloc(sizeof(t_philo *) * common->num_of_philos);
	run_threads(common, philo_threads, philos, &monitor);
	join_threads(common, philo_threads, &monitor);
	free(philo_threads);
	free_philos(philos, common->num_of_philos);
}

int	main(int argc, char **argv)
{
	if (is_input_valid(argc, argv))
		run_life_cycle(init_common_struct(argv));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
