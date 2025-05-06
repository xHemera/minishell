/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:21 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/06 16:54:48 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_total_len(char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			len++;
			j++;
		}
		i++;
	}
	return (len);
}

char	*copy_env(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	result = malloc(sizeof(char) * (get_total_len(env) + 1));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			result[k++] = env[i][j++];
		}
		i++;
	}
	result[k] = '\0';
	return (result);
}

void	print_env(t_shell *data)
{
	write(1, data->env.str, strlen(data->env.str));
}
