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