#include "../../../include/minishell.h"

int	is_valid_identifier(char *str)
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

int	handle_invalid_identifier(char *invalid_arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(invalid_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	update_existing_env_var(t_env *current, char *value)
{
	if (current->value)
		free(current->value);
	current->value = ft_strdup(value);
}

int	find_and_update_env_var(t_env *envp, char *key, char *value)
{
	t_env	*current;

	current = envp;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (value)
				update_existing_env_var(current, value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	add_new_env_var(t_env *envp, char *key, char *value)
{
	char	*key_dup;
	char	*value_dup;

	key_dup = ft_strdup(key);
	value_dup = NULL;
	if (value)
		value_dup = ft_strdup(value);
	env_add_back(&envp, env_new(key_dup, value_dup));
}
