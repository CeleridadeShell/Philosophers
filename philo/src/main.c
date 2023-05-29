/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/30 01:37:19 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philo_life()
{
	printf("Philosopher is eating.\n");
	printf("Philosopher is sleeping.\n");
	printf("Philosopher is thinking.\n");
	return (NULL);
}

void	run_life_cycle(t_args args)
{
	int			i;
	pthread_t	*philos;

	i = 0;
	philos = malloc(sizeof(pthread_t) * args.num_of_philos);
	while (i < args.num_of_philos)
	{
		pthread_create(&philos[i], NULL, &philo_life, NULL);
		pthread_join(philos[i], NULL);
		i++;
	}
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
