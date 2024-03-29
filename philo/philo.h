/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:32:09 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/29 15:37:38 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# include <pthread.h>
# include <sys/time.h>

# define NO -1
# define YES 1

typedef struct s_data
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	long			timer;
	int				eaten;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_eaten;
	pthread_mutex_t	message;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_data			*data;
	long			time_lst_eat;
	int				count_meal;
	int				name;
	struct s_philo	*next;
}					t_philo;

int		str_is_digit(char **str1);
void	ft_write_str(t_philo *philo, char *str, int flag);
int		return_free_philo_data(t_philo **philo1, t_data *data, int nbr_last);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		init_philo(t_philo **philo, char **argv);
int		check_data(int argc, char **argv);
long	ft_get_time(void);
int		destroy_mutx(pthread_mutex_t *ms,
			pthread_mutex_t *ml, pthread_mutex_t *e);
int		ft_philo_pthreds(t_philo **philo);
int		free_data(t_data	*data);

#endif