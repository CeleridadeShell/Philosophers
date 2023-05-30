/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:34:14 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/30 15:25:16 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philo_life(void *philo_num)
{
	printf("Philosopher %d is eating.\n", *(int *)philo_num);
	printf("Philosopher %d is sleeping.\n", *(int *)philo_num);
	printf("Philosopher %d is thinking.\n", *(int *)philo_num);
	free(philo_num);
	return (NULL);
}

void	run_life_cycle(t_args args)
{
	int			i;
	int			*i2;
	pthread_t	*philos;

	i = 0;
	philos = malloc(sizeof(pthread_t) * args.num_of_philos);
	while (i < args.num_of_philos)
	{
		i2 = malloc(sizeof(int));
		*i2 = i;
		if (pthread_create(&philos[i], NULL, &philo_life, (void *) i2))
		{
			free(philos);
			free(i2);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < args.num_of_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	free(philos);
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
