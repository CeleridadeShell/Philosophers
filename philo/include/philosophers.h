/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:35:47 by ccamargo          #+#    #+#             */
/*   Updated: 2023/06/03 20:07:08 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_common_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				opt_num_of_meals;
	int 			someone_died;
	long long		timestamp_init;
	long long		timestamp_current;
	pthread_mutex_t	**fork;
	pthread_mutex_t *print;

}	t_common_data;

typedef struct s_philo
{
	t_common_data	*common_data;
	int				id;
	int				meals_had;
	long long		last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philo;

//Validation Utils
int				is_input_valid(int argc, char **argv);
t_common_data	*convert_args(char **argv);

//Initialization Utils
void			initialize_philo(t_philo *philo, t_common_data *common, int i);

//Time Utils
void			set_timestamps(t_common_data *data);
long long		get_current_timestamp(t_philo *philo);

//Free Utils
void			free_philos(t_philo **philos, int num_of_philos);

int				ft_isdigit(int c);
int				ft_atoi(const char *nptr);

#endif
