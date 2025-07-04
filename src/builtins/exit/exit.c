/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:51:40 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/30 14:41:14 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;
	int	arg_count;

	exit_code = 0;
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	ft_putstr_fd("exit\n", 1);
	if (arg_count > 1)
	{
		if (!is_valid_number(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(2);
		}
		if (arg_count > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		exit_code = ft_atoi(args[1]) % 256;
	}
	exit(exit_code);
}
