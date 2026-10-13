/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:34:10 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/22 02:39:10 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_string(const char *str)
{
	if (!str)
		return (ft_write_string("(null)", 6));
	return (ft_write_string(str, ft_strlen(str)));
}

int	ft_convert(char type, va_list *args)
{
	if (type == 'c')
		return (ft_write_char((char)va_arg(*args, int)));
	if (type == 's')
		return (ft_print_string(va_arg(*args, char *)));
	if (type == 'p')
		return (ft_print_pointer((uintptr_t)va_arg(*args, void *)));
	if (type == 'd' || type == 'i')
		return (ft_print_signed(va_arg(*args, int)));
	if (type == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int)));
	if (type == 'x' || type == 'X')
		return (ft_print_hex(va_arg(*args, unsigned int), type));
	if (type == '%')
		return (ft_write_char('%'));
	return (ft_write_char(type));
}
