#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->is_builtin = 0;
	cmd->next = NULL;
	return (cmd);
}

static char	**create_new_args_array(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;
	char	*arg_dup;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	arg_dup = ft_strdup(arg);
	if (!arg_dup)
	{
		free(new_args);
		return (NULL);
	}
	return (new_args);
}

static void	copy_existing_args(char **new_args, char **old_args)
{
	int	i;

	i = 0;
	while (old_args && old_args[i])
	{
		new_args[i] = old_args[i];
		i++;
	}
}

int	cmd_add_arg(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;
	char	*arg_dup;

	if (!cmd || !arg)
		return (0);
	new_args = create_new_args_array(cmd, arg);
	if (!new_args)
		return (0);
	arg_dup = ft_strdup(arg);
	if (!arg_dup)
	{
		free(new_args);
		return (0);
	}
	count = 0;
	copy_existing_args(new_args, cmd->args);
	while (cmd->args && cmd->args[count])
		count++;
	new_args[count] = arg_dup;
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

void	cmd_clear(t_cmd **head)
{
	t_cmd	*tmp;
	t_cmd	*next;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free_cmd(tmp);
		tmp = next;
	}
	*head = NULL;
}
