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

typedef struct		s_data
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

typedef struct		s_philo
{
	// pthread_mutex_t	;
	// pthread_mutex_t	;
	
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_data			*data;
	long			time_lst_eat;
	int				count_meal;
	int				name;
	char			*name_char;
	int				len_name;
	struct s_philo			*next;
}					t_philo;

int
	ft_printf(char const *format, ...);
long	ft_atol(const char *str);
int	ft_isdigit(int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif