/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:22:21 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/03 18:14:55 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	free_philos(t_philo **philos, int num_of_philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philos[i]->left_fork);
	while (i < num_of_philos)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}
