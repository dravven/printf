
# include "ft_printf.h"

static int			ft_len(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char				*ft_itoa( int n)
{
	char			*str;
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = (n < 0 ? -n : n);
	len = ft_len(nb);
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * len + 1 + (n < 0 ? 1 : 0))))
		return (NULL);
	if (n < 0)
	{
		str[i] = '-';
		len++;
	}
	i = len - 1;
	while (nb >= 10)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	str[i] = nb % 10 + 48;
	str[len] = '\0';
	return (str);
}

void				ft_toa(int n, char *dest)
{
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = (n < 0 ? -n : n);
	len = ft_len(nb);
	i = 0;
	if (n < 0)
	{
		dest[i] = '-';
		len++;
	}
	i = len - 1;
	while (nb >= 10)
	{
		dest[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	dest[i] = nb % 10 + 48;
	dest[len] = '\0';
}

void                unsigned_ft_itoa(unsigned int n, char *dest)
{
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = (n < 0 ? -n : n);
	len = ft_len(nb);
	i = len - 1;
	while (nb >= 10)
	{
		dest[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	dest[i] = nb % 10 + 48;
	dest[len] = '\0';
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	pars_t *A;
	int i;

	if ((A = (pars_t *)malloc(sizeof(pars_t))) == NULL)
		return 0;

	A->len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			A->flag = 0;
			A->width = 0;
			A->pres = 0;
			A->flag_width = 0;
			A->flag_pres = 0;
			format++;
			if (*format == ' ')
				format++;
			parser(&format, A, &ap);
			i = ft_type_parse(&format, A);
			if (i == 1)
				format++;
			processor(A, &ap);

		}
		else
		{
			write(1, format, 1);
			format++;
			A->len++;
		}
	}
	va_end (ap);
	i = A->len;
	free(A);
	return i;
}



// NULL сделать
