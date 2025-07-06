#include "../../../include/minishell.h"

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
		if (!is_valid_identifier(supersplit[0]))
		{
			error = handle_invalid_identifier(cmd, supersplit, i);
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
