/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/17 00:04:55 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	run_life_cycle(t_common_data *common)
{
	pthread_t	*philo_threads;
	t_philo		**philos;

	philo_threads = (pthread_t *) malloc(sizeof(pthread_t) * \
	common->num_of_philos);
	philos = (t_philo **) malloc(sizeof(t_philo *) * common->num_of_philos);
	run_threads(common, philo_threads, philos);
	free(philo_threads);
	free_philos(philos, common->num_of_philos);
	free_common_data(common);
}

int	main(int argc, char **argv)
{	
	if (is_input_valid(argc, argv))
		run_life_cycle(init_common_data(argv));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
