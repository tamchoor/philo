/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:14:27 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/31 15:34:37 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	tp;
	long			time;

	if (gettimeofday(&tp, 0) != 0)
		return (-1);
	time = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (time);
}

void	free_sem(t_philo *philo)
{
	char	*name;

	sem_close(philo->s_meal_philo);
	name = ft_itoa(philo->name, len(philo->name));
	sem_unlink(name);
	free(name);
}

int	return_free_philo_data(t_philo **philo1, t_data *data, int nbr_last)
{
	t_philo	*philo;
	t_philo	*philo_for_free;

	close_sems((*philo1)->data->s_message,
		(*philo1)->data->s_eaten, (*philo1)->data->s_fork);
	if (data)
		free(data);
	if (*philo1 && nbr_last > 0)
	{
		philo = *philo1;
		while (philo->name != nbr_last)
		{
			philo_for_free = philo;
			philo = philo->next;
			free_sem(philo_for_free);
			free(philo_for_free);
			if (philo->name == (nbr_last))
			{
				free_sem(philo);
				free(philo);
				break ;
			}
		}
	}
	return (0);
}

void	ft_write_str(t_philo *philo, char *str, int flag)
{
	long	current_time;

	current_time = ft_get_time();
	current_time = current_time - philo->data->timer;
	sem_wait(philo->data->s_message);
	printf("%d %d %s\n", (int) current_time, philo->name, str);
	if (flag == YES)
		sem_post(philo->data->s_message);
}

int	close_sems(sem_t *message, sem_t *eaten, sem_t *forks)
{
	if (message != SEM_FAILED)
	{
		sem_close(message);
		sem_unlink("message");
	}
	if (eaten != SEM_FAILED)
	{
		sem_close(eaten);
		sem_unlink("eaten");
	}
	if (forks != SEM_FAILED)
	{
		sem_close(forks);
		sem_unlink("fork");
	}
	return (0);
}
