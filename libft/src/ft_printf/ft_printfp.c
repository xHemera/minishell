/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:32:27 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 15:27:16 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printfpx(uintptr_t uptr)
{
	char	*hex;
	int		len;

	len = 0;
	hex = "0123456789abcdef";
	if (uptr == 0)
		return (ft_printfc('0'));
	if (uptr >= 16)
		len += ft_printfpx(uptr / 16);
	ft_putchar_fd(hex[uptr % 16], 1);
	return (len + 1);
}

int	ft_printfp(void *ptr)
{
	uintptr_t		uptr;
	int				len;

	len = 0;
	if (!ptr)
		return (ft_printfs("(nil)"));
	uptr = (uintptr_t)ptr;
	len += ft_printfs("0x");
	len += ft_printfpx(uptr);
	return (len);
}
