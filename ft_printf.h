/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:00:18 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/22 23:50:09 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

# define HEX_LOW "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"

int	ft_printf(const char *format, ...);
int	ft_convert(char type, va_list *args);
int	ft_print_signed(int nbr);
int	ft_print_unsigned(unsigned int nbr);
int	ft_print_hex(unsigned int nbr, char type);
int	ft_print_pointer(uintptr_t ptr);
int	ft_write_char(char c);
int	ft_write_string(const char *str, int len);
int	ft_strlen(const char *str);
int	ft_putnbr_base(unsigned long nbr, const char *base, unsigned int base_len);

#endif
