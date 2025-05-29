/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:15:42 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 15:28:27 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printfx(unsigned int n, char special)
{
	char	*hex;
	int		len;

	len = 0;
	if (special == 'x')
		hex = "0123456789abcdef";
	else if (special == 'X')
		hex = "0123456789ABCDEF";
	else
		return (0);
	if (n == 0)
		return (ft_printfc('0'));
	if (n >= 16)
		len += ft_printfx(n / 16, special);
	ft_putchar_fd(hex[n % 16], 1);
	return (len + 1);
}
