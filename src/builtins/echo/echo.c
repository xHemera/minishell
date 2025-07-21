#include "minishell.h"

//Lors de l'appel, i = 0, j = 2 et newline = 1.
static void    echo_stdin(int newline)
{
    char    buffer[4096];
    ssize_t    bytes_read;

    bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        write(1, buffer, bytes_read);
    }
    if (newline)
        write(1, "\n", 1);
}

int    ft_echo(char **argv, int i, int j, int newline)
{
    while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
    {
        while (argv[i][j] == 'n')
            j++;
        if (argv[i][j] != '\0')
            break;
        newline = 0;
        i++;
    }
    
    if (!argv[i])  // No arguments provided
    {
        echo_stdin(newline);
        return (0);
    }

    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        if (argv[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
    return (0);
}
