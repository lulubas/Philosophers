/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:07:09 by lbastien          #+#    #+#             */
/*   Updated: 2023/01/23 18:45:46 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include "../../include/libft.h"

int	ft_printf(const char *input, ...)
{
	int		count;
	int		i;
	va_list	args;

	va_start(args, input);
	count = 0;
	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '%')
		{
			i++;
			count += ft_parse(input[i], args);
		}
		else
			count += ft_putchar(input[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int	ft_parse(const	char c, va_list args)
{
	int	count_chars;

	count_chars = 0;
	if (c == 'c')
		count_chars += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count_chars += ft_putstr(va_arg(args, const char *));
	else if (c == 'd' || c == 'i')
		count_chars = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count_chars = ft_putunbr(va_arg(args, unsigned int));
	else if (c == 'p')
		count_chars = ft_puthex(va_arg(args, unsigned long), c);
	else if (c == 'x' || c == 'X')
		count_chars = ft_puthex(va_arg(args, unsigned int), c);
	else if (c == '%')
		count_chars += ft_putchar('%');
	else if (c == 'E')
		write(2, "Error\n", 6);
	return (count_chars);
}
