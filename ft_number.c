/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:35:03 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/22 23:07:55 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_signed(int nbr)
{
	long	number;
	int		count;
	int		result;

	number = nbr;
	count = 0;
	if (number < 0)
	{
		result = ft_write_char('-');
		if (result < 0)
			return (-1);
		count += result;
		number = -number;
	}
	result = ft_putnbr_base((unsigned long)number, "0123456789", 10);
	if (result < 0)
		return (-1);
	return (count + result);
}

int	ft_print_unsigned(unsigned int nbr)
{
	return (ft_putnbr_base(nbr, "0123456789", 10));
}

int	ft_print_hex(unsigned int nbr, char type)
{
	if (type == 'X')
		return (ft_putnbr_base(nbr, HEX_UP, 16));
	return (ft_putnbr_base(nbr, HEX_LOW, 16));
}

int	ft_print_pointer(uintptr_t ptr)
{
	int	count;
	int	result;

	if (ptr == 0)
		return (ft_write_string("(nil)", 5));
	count = ft_write_string("0x", 2);
	if (count < 0)
		return (-1);
	result = ft_putnbr_base(ptr, HEX_LOW, 16);
	if (result < 0)
		return (-1);
	return (count + result);
}
