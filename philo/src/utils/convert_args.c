/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:18:48 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/05 00:31:28 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	init_mutexes(t_common_data *common)
{
	int	i;

	i = 0;
	common->fork = malloc(sizeof(pthread_mutex_t *) * common->num_of_philos);
	while (common->num_of_philos > i)
	{
		common->fork[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(common->fork[i], NULL);
		i++;
	}
	common->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->print, NULL);
	common->time = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->time, NULL);
	common->dead_or_alive = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->dead_or_alive, NULL);
	common->meals_had_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->meals_had_mutex, NULL);
	common->last_meal_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->last_meal_mutex, NULL);
}

t_common_data	*init_common_struct(char **argv)
{
	t_common_data	*common;

	common = malloc(sizeof(t_common_data));
	common->num_of_philos = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		common->opt_num_of_meals = ft_atoi(argv[5]);
	else
		common->opt_num_of_meals = -1;
	common->someone_died = 0;
	common->timestamp_init = 0;
	common->timestamp_current = -1;
	init_mutexes(common);
	return (common);
}
