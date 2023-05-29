/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:18:48 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/30 01:20:23 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_args	convert_args(char **argv)
{
	t_args	args;

	args.num_of_philos = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args.opt_num_of_meals = ft_atoi(argv[5]);
	else
		args.opt_num_of_meals = -1;
	return (args);
}
