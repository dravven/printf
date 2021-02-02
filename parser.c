# include "ft_printf.h"

void        parser(const char **format, pars_t *A, va_list *ap)
{
	flag_parser(format, A);

	width_parser(format, A, ap);

	prec_parser(format, A, ap);
}

void    ft_putchar(char c, pars_t *A)
{
	write(1, &c, 1);
	A->len++;
}

void    ft_putstr(char *str, pars_t *A)
{
	int i;

	i = 0;
	if (A->type == 's' && A->flag_pres == 1)
	{
		while (*str && i < A->pres)
		{
			ft_putchar(*str++, A);
//			A->width--;
			i++;
		}
	}
	else
	{
		while (*str)
			ft_putchar(*str++, A);
	}

}

void    ft_putstr_reverse(char *str, pars_t *A)
{
	int i;
	int h;

	i = 0;
	h = (int)strlen(str) - 1;
//	printf(" %d ", h);

	if (A->type == 's' && A->flag_pres == 1)
	{
		while (str[h] && i < A->pres)
		{
			ft_putchar(str[h--], A);
			A->width--;
			i++;
		}
	}
	else
	{
		while (h >= 0)
			ft_putchar(str[h--], A);
	}

}

void   flag_parser(const char **format, pars_t *A)
{
	while (**format == '0' || **format == '-')
	{
		if (**format == '0')
		{
			A->flag = 1;
			(*format)++;
		}
		if (**format == '-')
		{
			A->flag = 2;
			while (**format == '0' || **format == '-')
				(*format)++;

		}

	}
}

void   width_parser(const char **format, pars_t *A, va_list *ap)
{
	if (**format == '*')
	{
		A->flag_width = 1;
		A->width = va_arg (*ap, int);
		if (A->width < 0)
		{
			A->width *= -1;
			A->flag = 2;
		}
		(*format)++;
	}
	else if (**format >= '0' && **format <= '9')
	{
		A->flag_width = 1;
		while (**format >= '0' && **format <= '9')
		{
			A->width = A->width * 10 + (**format - 48);
			(*format)++;
		}
	}
	else
		A->type = 3;
}

void   prec_parser(const char **format, pars_t *A, va_list *ap)
{
	if (**format == '.')
	{
		(*format)++;
		A->flag_pres = 1;
		if (**format == '*')
		{
			A->pres = va_arg (*ap, int);
			if (A->pres < 0)
				A->flag_pres = 0;
			(*format)++;
		}
		else if (**format >= '0' && **format <= '9')
		{
			while(**format >= '0' && **format <= '9')
			{
				A->pres = A->pres * 10 + (**format - 48);
				(*format)++;
			}
		}
		else
			A->type = 3;
	}
}

int	ft_type_parse(const char **format, pars_t *A)
{
	if (**format == '%')
		A->type = '%';
	else if (**format == 'd')
		A->type = 'd';
	else if (**format == 'i') //
		A->type = 'i';
	else if (**format == 'u') //
		A->type = 'u';
	else if (**format == 'c') //
		A->type = 'c';
	else if (**format == 's')
		A->type = 's';
	else if (**format == 'p')
		A->type = 'p';
	else if (**format == 'x')
		A->type = 'x';
	else if (**format == 'X') //
		A->type = 'X';
	else
		return (0);
	return (1);
}

void    processor(pars_t *A, va_list *ap)
{
	if (A->type == '%')
	{
		type_proc(A);
	}
	if (A->type == 'd' || A->type == 'i')
	{
		type_d(A, ap);
	}
	if (A->type == 's')
	{
		type_s(ap, A);
	}
	if (A->type == 'x' || A->type == 'X')
	{
		type_x(ap, A);
	}
	if (A->type == 'p')
	{
		type_p(ap, A);
	}
	if (A->type == 'c')
	{
		type_c(ap, A);
	}
	if (A->type == 'u')
	{
		type_u(ap, A);
	}
	else
		A->type = 3;
}

void    type_d(pars_t *A, va_list *ap)
{
	char *str;
	int x;

	x = (int)va_arg (*ap, int);
//	printf("-%d-", x);

		str = ft_itoa(x);
	ft_print_d(str, A);
}



void    type_s(va_list *ap, pars_t *A)
{
	char *str;

	str = (char*)va_arg (*ap, char *);
	if (str == NULL)
		str = "(null)";

	ft_print_s(str, A);
}

void    type_of_x(char *str, char c)
{
	int i;
	int digit;

	i = 0;
	digit = 48;
	while (i < 10)
		str[i++] = digit++;
	if (c == 'x')
		digit = 97;
	else if (c == 'X')
		digit = 65;
	while (i < 16)
		str[i++] = digit++;
	str[i] = 0;
}


void    type_x(va_list *ap, pars_t *A)
{
	unsigned int x = va_arg (*ap, unsigned int);
	char ptr[16];
	char str[16];
	unsigned int num;
	int h;

	h = 0;
	type_of_x(ptr, A->type);
	if (x == 0)
		str[h++] = '0';
	while (x > 0)
	{
		num = x % 16;
		x = x / 16;
		str[h] = ptr[num];
		h++;
	}
	if (x == 16)
		str[h++] = x + 48;
	str[h]= '\0';
	ft_print_x(str, A);
}

void    type_p(va_list *ap, pars_t *A)
{
	void *p = va_arg (*ap, void *);
	unsigned long x = (unsigned long)p;
	char ptr[16];
	char str[16];
	unsigned long num;
	unsigned long n = x;
	int h;

	h = 0;
//	if (p == NULL)
//	printf("%d", (int)p);
	type_of_x(ptr, 'x');
	if (x == 0)
		str[h++] = '0';
	while (x > 0)
	{
		num = x % 16;
		x = x / 16;
		str[h] = ptr[num];
		h++;
	}
	if (x == 16)
		str[h++] = x + 48;

	str[h]= '\0';
	ft_print_p(str, A, n);
}

void    type_c(va_list *ap, pars_t *A)
{
	char c;

	c = (char)va_arg(*ap, int);
	ft_print_c(c, A);
}

void    type_u(va_list *ap, pars_t *A)
{
	char str[16];
	unsigned int i;
	unsigned int x;

	i = 0;
	x = (unsigned int)va_arg(*ap, unsigned int);

	unsigned_ft_itoa(x , str);
	ft_print_d(str, A);

}

void    type_proc(pars_t *A)
{
	char c;

	c = '%';

	ft_print_c(c, A);
}

void    ft_print_s(char *str, pars_t *A)
{
	int i;

	i = (int)strlen(str);
	if (A->pres < i && A->flag_pres == 1)
		i = A->pres;
	if (A->flag == 2)
		ft_putstr(str, A);
//	printf(" %d ", A->width);
	while (i < A->width--)
	{
		if (A->flag == 1)
			ft_putchar('0', A);
		else
			ft_putchar(' ', A);
	}
	if (A->flag != 2)
		ft_putstr(str, A);
}

int    ft_print_d(char *str, pars_t *A)
{
	int i;

	i = (int)strlen(str);
	if (A->flag_pres == 1 && A->pres == 0 && *str == '0') // мб убрать
		// среднее условие
	{
		str++;
		i = 0;
	}
	if (*str == '-')
		A->pres++;
	if (A->flag == 2)
	{
		if (*str == '-')
			ft_putchar(*str++, A);
		while (A->pres > i)
		{
			ft_putchar('0', A);
			i++;
		}

		ft_putstr(str, A);
	}
	if (*str == '-' && A->flag == 1 && A->flag_pres == 0)
		ft_putchar(*str++, A);
	while (i < A->width && A->width > A->pres)
	{
		if (A->flag == 1 && A->flag_pres == 0)
			ft_putchar('0', A);
		else
			ft_putchar(' ', A);
		A->width--;
	}
	if ((*str == '-' && A->flag != 1) || (*str == '-' && A->flag_pres == 1))
		ft_putchar(*str++, A);
	if (A->flag != 2)
	{
		while (A->pres > i++)
			ft_putchar('0', A);
		ft_putstr(str, A);
	}
	return (0);
}

int    ft_print_x(char *str, pars_t *A)
{
	int i;

	i = (int)strlen(str);
	if (A->flag_pres == 1 && A->pres == 0 && *str == '0')
	{
		str++;
		i = 0;
	}
	if (A->flag == 2)
		{
			while (A->pres > i)
			{
				ft_putchar('0', A);
				i++;
			}
			ft_putstr_reverse(str, A);
		}
	while (i < A->width && A->width > A->pres)
	{
		if (A->flag == 1 && A->flag_pres == 0)
			ft_putchar('0', A);
		else
			ft_putchar(' ', A);
		A->width--;
	}
	if (A->flag != 2)
	{
		while (A->pres > i++)
			ft_putchar('0', A);
		ft_putstr_reverse(str, A);
	}
	return (0);
}

int    ft_print_c(char str, pars_t *A)
{
	int i;

	i = 1;
	if (A->flag == 2)
		ft_putchar(str, A);
	while (i < A->width)
	{
		if (A->flag == 1)
			ft_putchar('0', A);
		else
			ft_putchar(' ', A);
		A->width--;
	}
//	while(A->pres > i)
//	{
//		ft_putchar('0', A);
//		i++;
//	}
	if (A->flag != 2)
		ft_putchar(str, A);
	return (0);
}

int    ft_print_p(char *str, pars_t *A, unsigned long x)
{
	int i;

	if (x == 0 && A->flag_pres == 1)
		str++;
//	else
		i = (int)strlen(str) + 2;
//	if (A->flag_pres == 1 && A->pres == 0 && *str == '0')
//	{
//		str++;
//		i = 2;
//	}
	if (A->flag == 2)
	{
		ft_putchar('0', A);
		ft_putchar('x', A);
		while (A->pres > i)
		{
			ft_putchar('0', A);
			i++;
		}
		
		ft_putstr_reverse(str, A);
	}
	while (i < A->width && A->width > A->pres)
	{
		if (A->flag == 1 && A->flag_pres == 0)
			ft_putchar('0', A);
		else
			ft_putchar(' ', A);
		A->width--;
	}
	if (A->flag != 2)
	{
		ft_putchar('0', A);
		ft_putchar('x', A);
		while (A->pres-- > i - 2)
			ft_putchar('0', A);
		A->width -= 2;
		ft_putstr_reverse(str, A);
	}
	return (0);
}