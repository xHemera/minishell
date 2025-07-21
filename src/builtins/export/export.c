#include "../../../include/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_invalid_identifier(char *invalid_arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(invalid_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	add_new_env_var(char **supersplit, t_env *envp)
{
	t_env	*current;
	char	*key_dup;
	char	*value_dup;

	current = envp;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		if (ft_strncmp(current->key, supersplit[0],
			ft_strlen(supersplit[0]) + 1) == 0)
		{
			if (supersplit[1])
			{
				if (current->value)
					free(current->value);
				current->value = ft_strdup(supersplit[1]);
			}
			return ;
		}
		current = current->next;
	}
	key_dup = ft_strdup(supersplit[0]);
	value_dup = supersplit[1] ? ft_strdup(supersplit[1]) : NULL;
	env_add_back(&envp, env_new(key_dup, value_dup));
}

static void	print_export_env(t_env *env)
{
	while (env)
	{
		if (env->value && ft_strncmp(env->value, " ", 1) != 0)
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			ft_printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static int	export_add(char **cmd, t_env *envp)
{
	char	**supersplit;
	int		i;
	int		error;

	i = 1;
	error = 0;
	while (cmd[i])
	{
		supersplit = ft_split(cmd[i], '=');
		if (!supersplit || !supersplit[0] || !is_valid_identifier(supersplit[0]))
		{
			if (!error)
				error = handle_invalid_identifier(cmd[i]);
			if (supersplit)
				free_split(supersplit);
			i++;
			continue ;
		}
		add_new_env_var(supersplit, envp);
		free_split(supersplit);
		i++;
	}
	return (error);
}

int	ft_export(t_cmd *cmd, t_env *envp, int argc)
{
	if (argc == 1)
	{
		print_export_env(envp);
	}
	else
	{
		while (envp->next)
			envp = envp->next;
		return (export_add(cmd->args, envp));
	}
	return (0);
}
