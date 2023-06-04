/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:18:48 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/04 23:39:36 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_common_data	*convert_args(char **argv)
{
	t_common_data	*common;
	int i;

	i = 0;
	common = malloc(sizeof(t_common_data));
	common->num_of_philos = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		common->opt_num_of_meals = ft_atoi(argv[5]);
	else
		common->opt_num_of_meals = -1;
	common->timestamp_init = 0;
	common->timestamp_current = -1;
	common->fork = malloc(sizeof(pthread_mutex_t *) * common->num_of_philos);
	common->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->print, NULL);
	common->someone_died = 0;
	common->dead_or_alive = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->dead_or_alive, NULL);
	common->time = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->time, NULL);
	common->meals_had_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->meals_had_mutex, NULL);
	common->last_meal_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(common->last_meal_mutex, NULL);
	while(common->num_of_philos > i)
	{
		common->fork[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(common->fork[i], NULL);
		i++;
	}
	return (common);
}
