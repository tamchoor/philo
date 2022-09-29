/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:32:19 by tamchoor          #+#    #+#             */
/*   Updated: 2022/03/29 15:34:16 by tamchoor         ###   ########.fr       */
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
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <string.h>

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
	sem_t			*s_meal;
	sem_t			*s_eaten;
	sem_t			*s_message;
	sem_t			*s_fork;
}					t_data;

typedef struct s_philo
{
	pid_t			pid;
	pthread_t		thread;
	sem_t			*s_meal_philo;
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
int		len(long nb);
char	*ft_itoa(int nb, int len);
int		close_sems(sem_t *message, sem_t *eaten, sem_t *forks);
int		check_death_and_eat(t_philo **philo);
void	wait_eaten(t_philo **philo, int flag_process);
void	philo_do(void *p);

#endif