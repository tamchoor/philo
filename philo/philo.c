#include "philo.h"

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


int		len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb, int len)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

int	check_data(int argc, char **argv)
{
	int	i;

	// ft_printf("argc = %d", argc);
	if (argc < 5 || argc > 6)
	{
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		//ft_printf("argv[%d] = %s\n", i, argv[i]);
		if (str_is_digit(&argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_data(char **argv, t_data *data)
{
	//int	nbr;

	data->nbr_philo = (int) ft_atol(argv[1]);
	data->time_die = (int) ft_atol(argv[2]);
	data->time_eat = (int) ft_atol(argv[3]);
	data->time_sleep = (int) ft_atol(argv[4]);
	if (argv[5])
		data->nbr_eat = (int) ft_atol(argv[5]);
	else
		data->nbr_eat = NO;
	if (data->nbr_philo == 0 || data->time_die == 0
		|| data->time_eat == 0 || data->time_sleep == 0
		|| (data->nbr_eat == 0))
		return (0);
	data->eaten = 0;
	return (1);
}

long	ft_get_time(void)
{
	struct timeval	tp;
	long			time;

	if (gettimeofday(&tp, 0) != 0)
		return (-1);
	time = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (time);
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

int return_free_philo_data(t_philo **philo1, t_data *data, int nbr_last)
{
	t_philo	*philo;
	t_philo	*philo_for_free;

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
			free(philo_for_free->name_char);
			free(philo_for_free);
			if (philo->name == nbr_last)
			{
				pthread_mutex_destroy(&philo->fork);
				free(philo->name_char);
				free(philo);
				break ;
			}
		}
	}
	return (0);
}

int	init_philo(t_philo **philo, char **argv)
{
	t_data	*data;
	int		count_philo;
	t_philo	*current_philo;
//	t_philo	*philo;

	
	data = (t_data *) malloc (1 * sizeof(t_data));
	if (!data)
		return (0);
	if (init_data(argv, data) == 0)
		return (return_free_philo_data(philo, data, 0));
	count_philo = 1;
//	philo = *philo1;
	while (count_philo <= data->nbr_philo)
	{
		current_philo = (t_philo *) malloc (1 * sizeof(t_philo));
		// printf("current_philo %p\n", current_philo);
		if (!current_philo)
			return (return_free_philo_data(philo, data, data->nbr_philo));
		current_philo->name = count_philo;
		// ft_printf("current_philo->name %d\n", current_philo->name);
		current_philo->count_meal = 0;
		current_philo->data = data;
		current_philo->time_lst_eat = 0;
		current_philo->len_name = len(current_philo->name);
		current_philo->name_char = ft_itoa(current_philo->name, current_philo->len_name);
		// printf("current_philo->data %p\n", current_philo->data);
		if (pthread_mutex_init(&current_philo->fork, NULL) != 0)
			return (return_free_philo_data(philo, data, data->nbr_philo));
		ft_add_next_philo(philo, current_philo);
		count_philo++;
	}
	current_philo->next = *philo;

	if (pthread_mutex_init(&data->message, NULL) != 0)
			return (return_free_philo_data(philo, data, data->nbr_philo));
	if (pthread_mutex_init(&data->m_eaten, NULL) != 0)
		return (return_free_philo_data(philo, data, data->nbr_philo));
	if (pthread_mutex_init(&data->m_meal, NULL) != 0)
		return (return_free_philo_data(philo, data, data->nbr_philo));

	//print
	// printf("phio->name|plo->ct_ml|data->t_die | t_eat | t_sleep  | nbr_eat \n");
	// printf(" %d nxt %d  |   %d     |     %d     |  %d   |   %d     | %d  \n",
	// 	(*philo)->name, (*philo)->next->name , (*philo)->count_meal, (*philo)->data->time_die, (*philo)->data->time_eat, (*philo)->data->time_sleep, (*philo)->data->nbr_eat);
	// 	(*philo) = (*philo)->next;
	// while ((*philo)->name != 1)
	// {
	// 	printf(" %d nxt %d  |   %d     |     %d     |  %d   |   %d     | %d  \n",
	// 	(*philo)->name, (*philo)->next->name , (*philo)->count_meal, (*philo)->data->time_die, (*philo)->data->time_eat, (*philo)->data->time_sleep, (*philo)->data->nbr_eat);
	// 	(*philo) = (*philo)->next;
	// }
	//end

	data->timer = ft_get_time();
	if (data->timer == -1)
		return (return_free_philo_data(philo, data, data->nbr_philo));

		//print
	// printf("  tim        |phio->name|plo->ct_ml|data->t_die | t_eat | t_sleep  | nbr_eat \n");
	// printf("%ld| %d nxt %d  |   %d     |     %d     |  %d   |   %d     | %d  \n",
	// 	philo->data->timer, philo->name, philo->next->name , philo->count_meal, philo->data->time_die, philo->data->time_eat, philo->data->time_sleep, philo->data->nbr_eat);
	// 	philo = philo->next;
	// while (philo->name != 1)
	// {
	// 	printf("%ld| %d nxt %d  |   %d     |     %d     |  %d   |   %d     | %d  \n",
	// 	philo->data->timer, philo->name, philo->next->name , philo->count_meal, philo->data->time_die, philo->data->time_eat, philo->data->time_sleep, philo->data->nbr_eat);
	// 	philo = philo->next;
	// }
	//end
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != 0)
	{
		count++;
	}
	return (count);
}

void	ft_write_str(t_philo *philo, char *str, int count, int flag)
{
	long	current_time;
	char	*u_sec;
	int		len_sec;

	current_time = ft_get_time();
	current_time = current_time - philo->data->timer;
	len_sec = len((int) current_time);

	u_sec = ft_itoa((int) current_time, len_sec);
	pthread_mutex_lock(&philo->data->message);
	write(1, u_sec, len_sec);
	if (current_time == 0)
		write(1, "0", 1);
	// ft_putnbr_fd(((int) current_time - timer), 1);
	write(1, " ", 1);
	write(1, philo->name_char, philo->len_name);
//	ft_putnbr_fd(name, 1);
	write(1, " ", 1);
	write(1, str, count);
	write(1, "\n", 1);
	if (flag == YES)
		pthread_mutex_unlock(&philo->data->message);
	free(u_sec);
}

void	*philo_do(void *p)
{
	t_philo	*philo;

	philo = (t_philo *) p;
	if (philo->name % 2 != 0)
	{
		//pthread_mutex_lock(&philo->data->message);
		ft_write_str(philo, "is thinking", 12, YES);
		//pthread_mutex_unlock(&philo->data->message);
		usleep((philo->data->time_eat * 1000) - 3000);
	}
	//printf("it is %d philo\n", philo->name);
	while (philo->data->nbr_eat > philo->count_meal || philo->data->nbr_eat == NO)
	{
		pthread_mutex_lock(&philo->fork);
		ft_write_str(philo, "has taken a fork", 17, YES);
		pthread_mutex_lock(&philo->next->fork);
		ft_write_str(philo, "has taken a fork", 17, YES);
		pthread_mutex_lock(&philo->data->m_meal);
		philo->time_lst_eat = ft_get_time();
		pthread_mutex_unlock(&philo->data->m_meal);
		ft_write_str(philo, "is eating", 10, YES);
		usleep((philo->data->time_eat * 1000) - 3000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo->count_meal++;
		if (philo->data->nbr_eat != NO && philo->data->nbr_eat == philo->count_meal)
		{
			pthread_mutex_lock(&philo->data->m_eaten);
			philo->data->eaten++;
			pthread_mutex_unlock(&philo->data->m_eaten);
			break ;
		}
		ft_write_str(philo, "is sleeping", 12, YES);
		usleep((philo->data->time_sleep * 1000) - 3000);
		ft_write_str(philo, "is thinking", 12, YES);
	}
	// if (philo->data->nbr_eat != NO)
	// {
	// 	ft_write_str(philo, "is eaten", 9, YES); // del
	// 	philo->data->eaten++;
	// }
	return ((void *) philo);
}

int check_who_died(t_philo **philo1, long current_time)
{
	int i;
	t_philo *philo;

	i = 1;
	philo = *philo1;
	while (philo->data->nbr_philo > i)
	{
		pthread_mutex_lock(&philo->data->m_meal);
		if ((int)(current_time - philo->time_lst_eat) >= (philo->data->time_die))
		{
			// printf("philo->time_lst_eat %ld| current_time %ld \n", philo->time_lst_eat, current_time);
			ft_write_str(philo, "died", 5, NO);
			return (YES);
		}
		pthread_mutex_unlock(&philo->data->m_meal);
		philo = philo->next;
		i++;
	}
	return (NO);

}

int ft_philo_pthreds(t_philo **philo)
{
	int		i;
	t_philo	*current_philo;
	long	current_time;
	int		death;
	int		eaten;



	i = 1;
	current_philo = *philo;
	while (i <= current_philo->data->nbr_philo)
	{
		pthread_create(&current_philo->thread, NULL, philo_do, (current_philo));
		current_philo = current_philo->next;
		i++;
	}
	death = NO;
	eaten = NO;
	while (death == NO && eaten == NO)
	{
		if ((*philo)->data->nbr_eat != NO)
		{
			//printf("(*philo)->data->eaten %d \n", (*philo)->data->eaten);
			pthread_mutex_lock(&(*philo)->data->m_eaten);
			if ((*philo)->data->eaten == (*philo)->data->nbr_philo)
			{
				pthread_mutex_lock(&(*philo)->data->message);
				write(1, "all philosophers have eaten", 28);
				eaten = YES;
				break ;
			}
			pthread_mutex_unlock(&(*philo)->data->m_eaten);
		}
		current_time = ft_get_time();
		death = check_who_died(philo, current_time);
		// if ((*philo)->data->nbr_eat != NO)
		// {
		// 	if ((*philo)->data->eaten == (*philo)->data->nbr_philo)
		// 	{
		// 		pthread_mutex_lock(&(*philo)->data->message);
		// 		write(1, "all philosophers have eaten", 28);
		// 		eaten = YES;
		// 	}
		// }
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	//ft_printf("time = ");
	if (check_data(argc, argv) == 0)
		return (0);
	philo = NULL;
	if (init_philo(&philo, argv) == 0)
		return (0);
	// ft_printf("\nnorm\n");



	// printf("  time       |phio->name|plo->ct_ml|data->t_die | t_eat | t_sleep  | nbr_eat \n");
	// printf("%ld| %d nxt %d  |   %d     |     %d     |  %d   |   %d     | %d  \n",
	// 	philo->data->timer, philo->name, philo->next->name , philo->count_meal, philo->data->time_die, philo->data->time_eat, philo->data->time_sleep, philo->data->nbr_eat);
	// philo = philo->next;
	// while (philo->name != 1)
	// {
	// 	printf("%ld| %d nxt %d  |   %d     |     %d     |  %d   |   %d     | %d  \n",
	// 	philo->data->timer, philo->name, philo->next->name , philo->count_meal, philo->data->time_die, philo->data->time_eat, philo->data->time_sleep, philo->data->nbr_eat);
	// 	philo = philo->next;
	// }

	ft_philo_pthreds(&philo);
	pthread_mutex_destroy(&philo->data->m_eaten);
	pthread_mutex_destroy(&philo->data->message);
	pthread_mutex_destroy(&philo->data->m_meal);
	return (return_free_philo_data(&philo, philo->data, philo->data->nbr_philo));
	
	return (0);
}
