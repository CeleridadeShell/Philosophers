/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:24:59 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/05 00:21:43 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	initialize_philo(t_philo *philo, t_common_data *common, int i)
{
	philo->common_data = common;
	philo->id = i;
	philo->meals_had = 0;
	philo->last_meal = 0;
	philo->left_fork = common->fork[i];
	philo->right_fork = common->fork[(i + 1) % common->num_of_philos];
	if ((i + 1) % common->num_of_philos == 0)
	{
		philo->right_fork = common->fork[i];
		philo->left_fork = common->fork[(i + 1) % common->num_of_philos];
	}
}
