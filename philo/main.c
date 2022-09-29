/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:55:04 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/29 19:20:39 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_data(t_data	*data)
{
	if (data)
		free (data);
	return (0);
}

long	ft_get_time(void)
{
	struct timeval	tp;
	long			time;

	if (gettimeofday(&tp, 0) != 0)
		return (-1);
	time = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (time);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	t_philo	*current_philo;

	if (check_data(argc, argv) == 0)
		return (0);
	philo = NULL;
	if (init_philo(&philo, argv) != 0)
	{
		if (ft_philo_pthreds(&philo) != 0)
		{
			current_philo = philo;
			i = 1;
			while (i++ <= philo->data->nbr_philo)
			{
				pthread_detach(current_philo->thread);
				current_philo = current_philo->next;
			}
		}
	}
	if (philo)
		return (return_free_philo_data(&philo, philo->data,
				philo->data->nbr_philo));
	return (0);
}
