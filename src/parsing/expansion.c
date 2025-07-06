#include "minishell.h"

int	ft_is_valid_var_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

int	ft_find_var_end(char *str, int start)
{
	int	i;

	i = start;
	if (str[i] == '?')
		return (i + 1);
	if (str[i] == '$')
		return (i + 1);
	if (!ft_is_valid_var_char(str[i], 1))
		return (i);
	while (str[i] && ft_is_valid_var_char(str[i], 0))
		i++;
	return (i);
}

char	*ft_extract_var_name(char *str, int start)
{
	int		end;
	char	*var_name;

	end = ft_find_var_end(str, start);
	var_name = ft_substr(str, start, end - start);
	return (var_name);
}
