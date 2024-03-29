/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:09:49 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/29 15:38:18 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	register unsigned char	u1;
	register unsigned char	u2;

	while (n-- > 0)
	{
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			return (0);
	}
	return (0);
}

int	str_is_digit(char **str1)
{
	int		i;
	char	*str;

	i = 0;
	str = *str1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	return_free_philo_data(t_philo **philo1, t_data *data, int nbr_last)
{
	t_philo	*philo;
	t_philo	*philo_for_free;

	destroy_mutx(&data->message, &data->m_eaten, &data->m_meal);
	if (data)
		free(data);
	if (*philo1 && nbr_last > 0)
	{
		philo = *philo1;
		while (philo->name != nbr_last)
		{
			philo_for_free = philo;
			philo = philo->next;
			pthread_mutex_destroy(&philo_for_free->fork);
			free(philo_for_free);
			if (philo->name == nbr_last)
			{
				pthread_mutex_destroy(&philo->fork);
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
	pthread_mutex_lock(&philo->data->message);
	printf("%d %d %s\n", (int) current_time, philo->name, str);
	if (flag == YES)
		pthread_mutex_unlock(&philo->data->message);
}
