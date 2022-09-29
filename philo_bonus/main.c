/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:06:26 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/31 15:23:11 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_process(t_philo **philo)
{
	int		i;
	t_philo	*current_philo;

	wait_eaten(philo, NO);
	current_philo = *philo;
	i = 1;
	while (i++ <= current_philo->data->nbr_philo)
	{
		current_philo->pid = fork();
		if (current_philo->pid == -1)
			return (0);
		if (current_philo->pid == 0)
		{
			philo_do(current_philo);
		}
		current_philo = current_philo->next;
	}
	if (check_death_and_eat(philo) == 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	t_philo	*current_philo;

	if (check_data(argc, argv) == 0)
		return (1);
	philo = NULL;
	if (init_philo(&philo, argv) != 0)
	{
		if (ft_philo_process(&philo) != 0)
		{
			current_philo = philo;
			i = 1;
			while (i++ <= philo->data->nbr_philo)
			{
				kill(current_philo->pid, SIGKILL);
				current_philo = current_philo->next;
			}
		}
	}
	if (philo)
		return (return_free_philo_data(&philo, philo->data,
				philo->data->nbr_philo));
	return (1);
}
