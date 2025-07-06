#include "minishell.h"

static char	*ft_get_special_var(char *var_name, int last_exit_code)
{
	if (ft_strlen(var_name) == 1)
	{
		if (var_name[0] == '?')
			return (ft_itoa(last_exit_code));
		if (var_name[0] == '$')
			return (ft_itoa(getpid()));
	}
	return (NULL);
}

char	*ft_get_var_value(char *var_name, t_env *env, int last_exit_code)
{
	char	*special_value;
	t_env	*current;

	special_value = ft_get_special_var(var_name, last_exit_code);
	if (special_value)
		return (special_value);
	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(current->key) == ft_strlen(var_name))
		{
			if (current->value)
				return (ft_strdup(current->value));
			return (ft_strdup(""));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_replace_variable(char *str, int start, int end, char *value)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*result;

	before = ft_substr(str, 0, start);
	after = ft_strdup(str + end);
	temp = ft_strjoin(before, value);
	result = ft_strjoin(temp, after);
	free(before);
	free(after);
	free(temp);
	return (result);
}

static char	*expand_variable_at_position(char *new_str, int *i, t_env *env,
	int last_exit_code)
{
	char	*var_name;
	char	*value;
	char	*temp_str;
	int		end;

	var_name = ft_extract_var_name(new_str, *i + 1);
	end = ft_find_var_end(new_str, *i + 1);
	value = ft_get_var_value(var_name, env, last_exit_code);
	temp_str = new_str;
	new_str = ft_replace_variable(new_str, *i, *i + 1 + (end - (*i + 1)),
			value);
	free(temp_str);
	free(var_name);
	*i += ft_strlen(value);
	free(value);
	return (new_str);
}

char	*ft_process_expansion(char *new_str, t_env *env, int last_exit_code)
{
	int		i;

	i = 0;
	while (new_str[i])
	{
		if (new_str[i] == '$' && new_str[i + 1]
			&& (ft_isalnum(new_str[i + 1]) || new_str[i + 1] == '_'
				|| new_str[i + 1] == '?' || new_str[i + 1] == '$'))
		{
			new_str = expand_variable_at_position(new_str, &i, env,
					last_exit_code);
		}
		else
			i++;
	}
	return (new_str);
}

char	*ft_expand_variables(char *str, t_env *env, int last_exit_code)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	return (ft_process_expansion(new_str, env, last_exit_code));
}
