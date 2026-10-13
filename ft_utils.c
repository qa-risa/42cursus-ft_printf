/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:37:24 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/22 22:23:24 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_putnbr_base(unsigned long nbr, const char *base, unsigned int base_len)
{
	int	count;
	int	result;

	count = 0;
	if (nbr >= base_len)
	{
		result = ft_putnbr_base(nbr / base_len, base, base_len);
		if (result < 0)
			return (-1);
		count += result;
	}
	result = ft_write_char(base[nbr % base_len]);
	if (result < 0)
		return (-1);
	return (count + result);
}
