//
// Created by Dsons on 23.01.2021.
//

#ifndef MAIN_C_FT_PRINTF_H
#define MAIN_C_FT_PRINTF_H
# include "stdarg.h"
# include "string.h"
# include "stdio.h"
# include "unistd.h"
# include "string.h"
# include <stdio.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>

typedef struct		pars
{
	int len;
	int flag;
	int width;
	int flag_width;
	int pres;
	int flag_pres;
	char type;
}                   pars_t;

void        parser(const char **format, pars_t *A, va_list *ap);

int         ft_printf(const char *format, ...);

void				ft_toa(int n, char *dest);

void    reverse_str(char *str, pars_t *A);

void                unsigned_ft_itoa(unsigned int n, char *dest);

int	    ft_type_parse(const char **format, pars_t *A);

void    processor(pars_t *A, va_list *ap);

void    type_s(va_list *ap, pars_t *A);

void    type_x(va_list *ap, pars_t *A);

void    ft_print_type(char *str, pars_t *A);

void    type_d(pars_t *A, va_list *ap);

void   flag_parser(const char **format, pars_t *A);

void   width_parser(const char **format, pars_t *A, va_list *ap);

void   prec_parser(const char **format, pars_t *A, va_list *ap);

void    type_p(va_list *ap, pars_t *A);

void    type_of_x(char *str, char c);

void    type_c(va_list *ap, pars_t *A);

void    type_u(va_list *ap, pars_t *A);

void    type_proc(pars_t *A);

void    ft_putstr(char *str, pars_t *A);

void    ft_putchar(char c, pars_t *A);

void    ft_print_s(char *str, pars_t *A);

int    ft_print_d(char *str, pars_t *A);

int    ft_print_x(char *str, pars_t *A);

void    ft_putstr_reverse(char *str, pars_t *A);

int    ft_print_c(char str, pars_t *A);

int    ft_print_p(char *str, pars_t *A, unsigned long x);

char				*ft_itoa( int n);

#endif //MAIN_C_FT_PRINTF_H
