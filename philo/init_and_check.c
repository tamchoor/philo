/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:09:03 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/31 14:51:11 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_data(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (str_is_digit(&argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	destroy_mutx(pthread_mutex_t *ms, pthread_mutex_t *ml, pthread_mutex_t *e)
{
	if (ms != NULL)
		pthread_mutex_destroy(ms);
	if (ml != NULL)
		pthread_mutex_destroy(ml);
	if (e != NULL)
		pthread_mutex_destroy(e);
	return (0);
}

int	init_data(char **argv, t_data *data)
{
	data->nbr_philo = (int) ft_atol(argv[1]);
	data->time_die = (int) ft_atol(argv[2]);
	data->time_eat = (int) ft_atol(argv[3]);
	data->time_sleep = (int) ft_atol(argv[4]);
	if (argv[5])
		data->nbr_eat = (int) ft_atol(argv[5]);
	else
		data->nbr_eat = NO;
	if (data->nbr_philo <= 0 || data->time_die <= 0
		|| data->time_eat <= 0 || data->time_sleep <= 0
		|| (data->nbr_eat != NO && data->nbr_eat <= 0))
		return (0);
	data->eaten = 0;
	if (pthread_mutex_init(&data->message, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->m_eaten, NULL) != 0)
		destroy_mutx(&data->message, NULL, NULL);
	if (pthread_mutex_init(&data->m_meal, NULL) != 0)
		destroy_mutx(&data->message, &data->m_eaten, NULL);
	data->timer = ft_get_time();
	if (data->timer == -1)
		destroy_mutx(&data->message, &data->m_eaten, &data->m_meal);
	return (1);
}

void	ft_add_next_philo(t_philo **alst, t_philo *new1)
{
	t_philo	*ptr;

	if (*alst != NULL)
	{
		ptr = *alst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new1;
		ptr->next->next = NULL;
	}
	else
	{
		*alst = new1;
		(*alst)->next = NULL;
	}
}

int	init_philo(t_philo **philo, char **argv)
{
	t_data	*data;
	int		count_philo;
	t_philo	*current_philo;

	data = (t_data *) malloc (1 * sizeof(t_data));
	if (!data || (data && init_data(argv, data) == 0))
		return (free_data(data));
	count_philo = 1;
	while (count_philo <= data->nbr_philo)
	{
		current_philo = (t_philo *) malloc (1 * sizeof(t_philo));
		if (!current_philo)
			return (return_free_philo_data(philo, data, count_philo));
		current_philo->name = count_philo++;
		current_philo->count_meal = 0;
		current_philo->data = data;
		current_philo->time_lst_eat = data->timer;
		if (pthread_mutex_init(&current_philo->fork, NULL) != 0)
			return (return_free_philo_data(philo, data, (count_philo - 1)));
		ft_add_next_philo(philo, current_philo);
	}
	current_philo->next = *philo;
	return (1);
}
