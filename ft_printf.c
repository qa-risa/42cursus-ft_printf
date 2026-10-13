/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:36:27 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/22 02:38:51 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_process_char(const char *format, int *index, va_list *args)
{
	int	result;

	if (format[*index] == '%' && format[*index + 1])
	{
		(*index)++;
		result = ft_convert(format[*index], args);
		(*index)++;
		return (result);
	}
	result = ft_write_char(format[*index]);
	(*index)++;
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		index;
	int		count;
	int		result;

	if (!format)
		return (-1);
	index = 0;
	count = 0;
	va_start(args, format);
	while (format[index])
	{
		result = ft_process_char(format, &index, &args);
		if (result < 0)
		{
			va_end(args);
			return (-1);
		}
		count += result;
	}
	va_end(args);
	return (count);
}
