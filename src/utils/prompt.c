/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:49:38 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 12:32:07 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_last_dir(char *cwd)
{
	char	*last_dir;

	getcwd(cwd, 1024);
	last_dir = ft_strrchr(cwd, '/');
	if (last_dir)
		return (last_dir + 1);
	return (cwd);
}

static size_t	get_prompt_len(char *user, char *last_dir)
{
	return (ft_strlen(CYAN) + ft_strlen(TITLE) + ft_strlen(GREEN)
		+ ft_strlen(user) + ft_strlen("@") + ft_strlen(YELLOW)
		+ ft_strlen(last_dir) + ft_strlen(RESET) + 2);
}

static void	build_prompt(char *prompt, char *user, char *last_dir)
{
	ft_strlcat(prompt, CYAN, 512);
	ft_strlcat(prompt, TITLE, 512);
	ft_strlcat(prompt, GREEN, 512);
	ft_strlcat(prompt, user, 512);
	ft_strlcat(prompt, "@", 512);
	ft_strlcat(prompt, YELLOW, 512);
	ft_strlcat(prompt, last_dir, 512);
	ft_strlcat(prompt, RESET, 512);
	ft_strlcat(prompt, "$ ", 512);
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char	*prompt;
	char	*user;
	char	*last_dir;
	size_t	prompt_len;

	user = getenv("USER");
	last_dir = get_last_dir(cwd);
	prompt_len = get_prompt_len(user, last_dir);
	prompt = malloc(prompt_len + 1);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	build_prompt(prompt, user, last_dir);
	return (prompt);
}
