/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:49:38 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 12:03:28 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_time(char *time_str)
{
	time_t		t;
	struct tm	*info;

	time(&t);
	info = localtime(&t);
	strftime(time_str, 9, "%H:%M:%S", info);
}

static char	*get_last_dir(char *cwd)
{
	char	*last_dir;

	getcwd(cwd, 1024);
	last_dir = strrchr(cwd, '/');
	if (last_dir)
		return (last_dir + 1);
	return (cwd);
}

char	*get_prompt(void)
{
	char	time_str[9];
	char	cwd[1024];
	char	*prompt;
	char	*user;
	char	*last_dir;

	get_time(time_str);
	user = getenv("USER");
	last_dir = get_last_dir(cwd);
	prompt = malloc(512);
	if (!prompt)
		return (NULL);
	snprintf(prompt, 512, "%s[%s] %s@%s:%s%s$ %s",
		CYAN, time_str, GREEN, user, YELLOW, last_dir, RESET);
	return (prompt);
}
