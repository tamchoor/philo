/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:09:10 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/29 18:57:08 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_write_str(philo, "has taken a fork", YES);
	pthread_mutex_lock(&philo->next->fork);
	ft_write_str(philo, "has taken a fork", YES);
	pthread_mutex_lock(&philo->data->m_meal);
	philo->time_lst_eat = ft_get_time();
	pthread_mutex_unlock(&philo->data->m_meal);
	ft_write_str(philo, "is eating", YES);
	usleep((philo->data->time_eat * 1000) - 2000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	philo->count_meal++;
}

void	*philo_do(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	if (philo->name % 2 != 0 && philo->data->nbr_philo != 1)
	{
		ft_write_str(philo, "is thinking", YES);
		usleep((philo->data->time_eat * 1000) - 5000);
	}
	while (1)
	{
		ft_philo_eating(philo);
		if (philo->data->nbr_eat != NO
			&& philo->data->nbr_eat == philo->count_meal)
		{
			pthread_mutex_lock(&philo->data->m_eaten);
			philo->data->eaten++;
			pthread_mutex_unlock(&philo->data->m_eaten);
		}
		ft_write_str(philo, "is sleeping", YES);
		usleep((philo->data->time_sleep * 1000) - 2000);
		ft_write_str(philo, "is thinking", YES);
	}
	return ((void *) philo);
}

int	check_who_died(t_philo **philo1, long current_time)
{
	int		i;
	t_philo	*philo;

	i = 1;
	philo = *philo1;
	while (philo->data->nbr_philo >= i)
	{
		pthread_mutex_lock(&philo->data->m_meal);
		if ((int)(current_time - philo->time_lst_eat)
			>= (philo->data->time_die))
		{
			pthread_mutex_lock(&philo->data->message);
			printf("%d %d died\n", (int)(current_time - philo->data->timer),
				philo->name);
			return (YES);
		}
		pthread_mutex_unlock(&philo->data->m_meal);
		philo = philo->next;
		i++;
	}
	return (NO);
}

int	create_threads(t_philo **philo)
{
	int		i;
	t_philo	*current_philo;

	i = 1;
	current_philo = (*philo);
	while (i++ <= current_philo->data->nbr_philo)
	{
		if (pthread_create(&current_philo->thread,
				NULL, philo_do, (current_philo)) != 0)
			return (0);
		current_philo = current_philo->next;
	}
	return (1);
}

int	ft_philo_pthreds(t_philo **philo)
{
	if (create_threads(philo) == 0)
		return (0);
	while (check_who_died(philo, ft_get_time()) == NO)
	{
		if ((*philo)->data->nbr_eat != NO)
		{
			pthread_mutex_lock(&(*philo)->data->m_eaten);
			if ((*philo)->data->eaten == (*philo)->data->nbr_philo)
			{
				pthread_mutex_lock(&(*philo)->data->message);
				write(1, "all philosophers have eaten\n", 29);
				break ;
			}
			pthread_mutex_unlock(&(*philo)->data->m_eaten);
		}
	}
	return (1);
}
