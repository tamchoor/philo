/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:14:04 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/31 15:21:48 by tamchoor         ###   ########.fr       */
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
	data->eaten = NO;
	sem_unlink("message");
	sem_unlink("eaten");
	sem_unlink("forks");
	data->s_message = sem_open("message", O_CREAT, S_IRWXU, 1);
	data->s_eaten = sem_open("eaten", O_CREAT, S_IRWXU, (data->nbr_philo));
	data->s_fork = sem_open("forks", O_CREAT, S_IRWXU, (data->nbr_philo));
	data->timer = ft_get_time();
	if (data->s_eaten == SEM_FAILED || data->s_message == SEM_FAILED
		|| data->s_fork == SEM_FAILED || (data->timer == -1))
		return (close_sems(data->s_message,
				data->s_eaten, data->s_fork));
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

int	init_current_philo(t_philo	*crnt_phil, t_data	*data, int count_philo)
{
	char	*name;

	crnt_phil->name = count_philo;
	crnt_phil->count_meal = 0;
	crnt_phil->data = data;
	crnt_phil->time_lst_eat = data->timer;
	name = ft_itoa(crnt_phil->name, len(crnt_phil->name));
	sem_unlink(name);
	crnt_phil->s_meal_philo = sem_open(name, O_CREAT, S_IRWXU, 1);
	free(name);
	if (crnt_phil->s_meal_philo == SEM_FAILED)
	{
		return (0);
	}
	return (1);
}

int	init_philo(t_philo **philo, char **argv)
{
	t_data	*data;
	int		count_philo;
	t_philo	*crnt_phil;

	data = (t_data *) malloc (1 * sizeof(t_data));
	if (!data || (data && init_data(argv, data) == 0))
	{
		if (data)
			free (data);
		return (0);
	}
	count_philo = 1;
	while (count_philo <= data->nbr_philo)
	{
		crnt_phil = (t_philo *) malloc (1 * sizeof(t_philo));
		if (!crnt_phil || !init_current_philo(crnt_phil, data, count_philo++))
		{
			free (data);
			return (close_sems(data->s_message, data->s_eaten, data->s_fork));
		}
		ft_add_next_philo(philo, crnt_phil);
	}
	crnt_phil->next = *philo;
	return (1);
}
