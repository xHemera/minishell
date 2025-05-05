/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:20:43 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 16:56:04 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	redirect(char special, va_list args)
{
	if (special == 'c')
		return (ft_printfc((char)va_arg(args, int)));
	else if (special == 's')
		return (ft_printfs(va_arg(args, char *)));
	else if (special == 'p')
		return (ft_printfp(va_arg(args, void *)));
	else if (special == 'd' || special == 'i')
		return (ft_printfd(va_arg(args, int)));
	else if (special == 'u')
		return (ft_printfu(va_arg(args, unsigned int)));
	else if (special == 'x' || special == 'X')
		return (ft_printfx(va_arg(args, unsigned int), special));
	else if (special == '%')
		ft_putchar_fd('%', 1);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			j += redirect(format[i], args);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			j ++;
		}
		i ++;
	}
	va_end(args);
	return (j);
}
