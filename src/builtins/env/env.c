#include "minishell.h"

int	ft_env(t_env *envp)
{
	while (envp)
	{
		if (envp->value)
			ft_printf("%s=%s\n", envp->key, envp->value);
		else
			ft_printf("%s=\n", envp->key);
		envp = envp->next;
	}
	return (1);
}
