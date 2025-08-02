#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void free_heredoc_file(t_cmd *cmd)
{
	if (cmd->heredoc)
	{
		free(cmd->heredoc);
		cmd->heredoc = NULL;
	}
}
