/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:01:38 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/31 15:23:39 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eating(t_philo	*philo)
{
	sem_wait(philo->data->s_fork);
	ft_write_str(philo, "has taken a fork", YES);
	sem_wait(philo->data->s_fork);
	ft_write_str(philo, "has taken a fork", YES);
	sem_wait(philo->s_meal_philo);
	philo->time_lst_eat = ft_get_time();
	sem_post(philo->s_meal_philo);
	ft_write_str(philo, "is eating", YES);
	usleep((philo->data->time_eat * 1000) - 3000);
	sem_post(philo->data->s_fork);
	sem_post(philo->data->s_fork);
	philo->count_meal++;
}

void	*philo_death(void *p)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *) p;
	while (1)
	{
		current_time = ft_get_time();
		sem_wait(philo->s_meal_philo);
		if ((int)(current_time - philo->time_lst_eat)
				>= (philo->data->time_die))
		{
			ft_write_str(philo, "died", NO);
			exit(0);
		}
		sem_post(philo->s_meal_philo);
		usleep(500);
	}
	return ((void *) philo);
}

void	philo_do(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	pthread_create(&philo->thread, NULL, philo_death, philo);
	while (1)
	{
		ft_philo_eating(philo);
		if (philo->data->nbr_eat != NO
			&& philo->data->nbr_eat == philo->count_meal)
		{
			sem_post(philo->data->s_eaten);
		}
		ft_write_str(philo, "is sleeping", YES);
		usleep((philo->data->time_sleep * 1000) - 3000);
		ft_write_str(philo, "is thinking", YES);
	}
	exit (1);
}

void	wait_eaten(t_philo **philo, int flag_process)
{
	int	i;

	i = 1;
	while (i++ <= (*philo)->data->nbr_philo)
		sem_wait((*philo)->data->s_eaten);
	if (flag_process == YES)
		exit(1);
}

int	check_death_and_eat(t_philo **philo)
{
	pid_t	pid_eaten;
	int		status;

	if ((*philo)->data->nbr_eat != NO)
	{
		pid_eaten = fork();
		if (pid_eaten == -1)
			return (0);
		if (pid_eaten == 0)
			wait_eaten(philo, YES);
	}
	waitpid(0, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			sem_wait((*philo)->data->s_message);
			write(1, "all philosophers have eaten\n", 29);
		}
	}
	if ((*philo)->data->nbr_eat != NO)
		kill(pid_eaten, SIGKILL);
	return (1);
}
