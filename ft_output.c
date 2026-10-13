/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:35:18 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/22 23:49:17 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_char(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_write_string(const char *str, int len)
{
	if (write(1, str, len) < 0)
		return (-1);
	return (len);
}
