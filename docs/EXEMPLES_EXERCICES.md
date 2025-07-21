# 💻 Exemples de Code et Exercices Pratiques - Minishell

## 📋 Table des Matières
1. [Exemples de Code Complets](#exemples)
2. [Exercices Progressifs](#exercices)
3. [Patterns de Programmation](#patterns)
4. [Gestion d'Erreurs](#erreurs)
5. [Optimisations](#optimisations)

---

## 1. Exemples de Code Complets {#exemples}

### 🔧 Structure Complète du Header

```c
#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/include/libft.h"

/* ************************************************************************** */
/*                              STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_env
{
    struct s_env    *prev;
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_cmd
{
    char            *name;
    char            **args;
    char            *input_file;
    char            *output_file;
    int             append;
    char            *heredoc;
    bool            is_builtin;
    struct s_cmd    *next;
}   t_cmd;

/* ************************************************************************** */
/*                           GLOBAL VARIABLES                                */
/* ************************************************************************** */

extern int  g_signal_received;

/* ************************************************************************** */
/*                            FUNCTION PROTOTYPES                            */
/* ************************************************************************** */

// Parsing
char    **tokenize_improved(const char *str);
t_cmd   *parse_segment(char *segment);
char    *ft_expand_variables(char *str, t_env *env, int last_exit_code);

// Execution
int     exec_cmd(t_cmd *cmd, t_env **env);
int     exec_pipeline(t_cmd *cmd_list, t_env **env);

// Built-ins
int     ft_cd(char **args, t_env *env);
int     ft_echo(char **args);
int     ft_export(t_cmd *cmd, t_env *env, int argc);

// Environment
t_env   *env_init(char **envp);
char    *get_env_value(t_env *env, char *key);
void    set_env_value(t_env *env, char *key, char *value);

// Utils
void    free_cmd(t_cmd *cmd);
void    free_env(t_env **env);
void    setup_signals(void);

#endif
```

### 🚀 Main Function Complète

```c
#include "minishell.h"

int g_signal_received = 0;

int main(int argc, char **argv, char **envp)
{
    t_env   *env;

    (void)argc;
    (void)argv;

    // 1. Configuration initiale
    setup_signals();

    // 2. Initialisation de l'environnement
    env = env_init(envp);
    if (!env)
    {
        ft_putstr_fd("minishell: failed to initialize environment\n", 2);
        return (1);
    }

    // 3. Message de bienvenue (optionnel)
    ft_putstr_fd("🐚 Minishell started successfully!\n", 1);
    ft_putstr_fd("Type 'exit' to quit.\n", 1);

    // 4. Boucle principale
    minishell_loop(&env);

    // 5. Nettoyage final
    free_env(&env);
    rl_clear_history();

    return (g_signal_received);
}
```

### 🔄 Boucle Principale Détaillée

```c
void minishell_loop(t_env **env)
{
    char    *line;
    char    *trimmed_line;

    while (1)
    {
        // 1. Affichage du prompt personnalisé
        line = readline(create_prompt(*env));

        // 2. Gestion de Ctrl+D (EOF)
        if (!line)
        {
            ft_putstr_fd("exit\n", 1);
            cleanup_and_exit(g_signal_received);
        }

        // 3. Reset du signal après interruption
        if (g_signal_received == 130)
            g_signal_received = 0;

        // 4. Traitement de la ligne
        trimmed_line = ft_strtrim(line, " \t\n");
        if (trimmed_line && *trimmed_line)
        {
            add_history(line);
            parse_and_exec(trimmed_line, env);
        }

        // 5. Nettoyage
        free(line);
        free(trimmed_line);
    }
}

char *create_prompt(t_env *env)
{
    char    *pwd;
    char    *user;
    char    *prompt;
    char    *temp;

    pwd = get_env_value(env, "PWD");
    user = get_env_value(env, "USER");

    if (!pwd)
        pwd = "unknown";
    if (!user)
        user = "user";

    // Format: user@minishell:pwd>
    temp = ft_strjoin(user, "@minishell:");
    prompt = ft_strjoin(temp, pwd);
    free(temp);
    temp = ft_strjoin(prompt, "> ");
    free(prompt);

    return (temp);
}
```

### 🔍 Tokenisation Avancée

```c
char **tokenize_improved(const char *str)
{
    char    **tokens;
    int     count;
    int     i;
    int     token_idx;

    if (!str)
        return (NULL);

    // 1. Compter les tokens
    count = count_tokens_improved(str);
    if (count == 0)
        return (NULL);

    // 2. Allouer le tableau
    tokens = malloc(sizeof(char *) * (count + 1));
    if (!tokens)
        return (NULL);

    // 3. Extraire chaque token
    i = 0;
    token_idx = 0;

    while (str[i] && token_idx < count)
    {
        // Ignorer les espaces
        i = skip_spaces(str, i);
        if (!str[i])
            break;

        // Traiter les opérateurs
        if (is_operator_char(str[i]))
        {
            tokens[token_idx] = extract_operator(str, &i);
        }
        // Traiter les mots (avec ou sans quotes)
        else
        {
            tokens[token_idx] = extract_word(str, &i);
        }

        if (!tokens[token_idx])
        {
            free_tokens_partial(tokens, token_idx);
            return (NULL);
        }

        token_idx++;
    }

    tokens[token_idx] = NULL;
    return (tokens);
}

int count_tokens_improved(const char *str)
{
    int i = 0;
    int count = 0;
    int in_word = 0;

    while (str[i])
    {
        if (is_whitespace(str[i]))
        {
            if (in_word)
            {
                count++;
                in_word = 0;
            }
        }
        else if (is_operator_char(str[i]))
        {
            if (in_word)
            {
                count++;
                in_word = 0;
            }
            count++; // L'opérateur lui-même

            // Gérer les opérateurs doubles (<<, >>)
            if ((str[i] == '<' && str[i + 1] == '<') ||
                (str[i] == '>' && str[i + 1] == '>'))
                i++;
        }
        else
        {
            if (!in_word)
                in_word = 1;

            // Gérer les quotes
            if (str[i] == '\'' || str[i] == '"')
            {
                char quote = str[i];
                i++;
                while (str[i] && str[i] != quote)
                    i++;
            }
        }

        if (str[i])
            i++;
    }

    if (in_word)
        count++;

    return (count);
}
```

### 🎯 Expansion de Variables Complète

```c
char *ft_expand_variables(char *str, t_env *env, int last_exit_code)
{
    char    *result;
    char    *temp;
    int     i;
    int     start;

    if (!str)
        return (NULL);

    result = ft_strdup(str);
    if (!result)
        return (NULL);

    i = 0;
    while (result[i])
    {
        if (result[i] == '$' && result[i + 1])
        {
            start = i;
            i++; // Passer le '$'

            // Variable spéciale $? ou $$
            if (result[i] == '?' || result[i] == '$')
            {
                temp = expand_special_var(result, start, result[i],
                                        last_exit_code);
                free(result);
                result = temp;
                if (!result)
                    return (NULL);
                i = start; // Reprendre depuis le début de l'expansion
            }
            // Variable normale $VAR
            else if (ft_isalpha(result[i]) || result[i] == '_')
            {
                temp = expand_normal_var(result, start, env);
                free(result);
                result = temp;
                if (!result)
                    return (NULL);
                i = start; // Reprendre depuis le début de l'expansion
            }
            else
            {
                i++; // Juste un '$' isolé, continuer
            }
        }
        else
        {
            i++;
        }
    }

    return (result);
}

char *expand_special_var(char *str, int start, char var_type, int last_exit_code)
{
    char    *value;
    char    *result;

    if (var_type == '?')
        value = ft_itoa(last_exit_code);
    else if (var_type == '$')
        value = ft_itoa(getpid());
    else
        return (ft_strdup(str)); // Erreur, ne pas modifier

    if (!value)
        return (NULL);

    result = replace_substring(str, start, start + 2, value);
    free(value);

    return (result);
}

char *expand_normal_var(char *str, int start, t_env *env)
{
    int     end;
    char    *var_name;
    char    *value;
    char    *result;

    // Trouver la fin du nom de variable
    end = start + 1; // Après le '$'
    while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
        end++;

    // Extraire le nom
    var_name = ft_substr(str, start + 1, end - start - 1);
    if (!var_name)
        return (NULL);

    // Récupérer la valeur
    value = get_env_value(env, var_name);
    if (!value)
        value = ""; // Variable non définie = chaîne vide

    // Remplacer dans la chaîne
    result = replace_substring(str, start, end, value);

    free(var_name);
    return (result);
}

char *replace_substring(char *str, int start, int end, char *replacement)
{
    int     new_len;
    char    *result;
    int     i, j;

    new_len = ft_strlen(str) - (end - start) + ft_strlen(replacement);
    result = malloc(new_len + 1);
    if (!result)
        return (NULL);

    // Copier avant le remplacement
    i = 0;
    j = 0;
    while (i < start)
        result[j++] = str[i++];

    // Copier le remplacement
    i = 0;
    while (replacement[i])
        result[j++] = replacement[i++];

    // Copier après le remplacement
    i = end;
    while (str[i])
        result[j++] = str[i++];

    result[j] = '\0';
    return (result);
}
```

### 🔧 Parsing de Commande Complet

```c
t_cmd *parse_segment(char *segment)
{
    t_cmd   *cmd;
    char    **tokens;
    int     i;

    if (!segment || !*segment)
        return (NULL);

    // 1. Créer la structure command
    cmd = cmd_new();
    if (!cmd)
        return (NULL);

    // 2. Tokeniser le segment
    tokens = tokenize_improved(segment);
    if (!tokens)
    {
        free_cmd(cmd);
        return (NULL);
    }

    // 3. Parser les tokens
    i = 0;
    while (tokens[i])
    {
        if (is_redirection_token(tokens[i]))
        {
            if (!handle_redirection(cmd, tokens, &i))
            {
                free_cmd(cmd);
                free_tokens(tokens);
                return (NULL);
            }
        }
        else
        {
            // Ajouter comme commande ou argument
            add_argument_to_cmd(cmd, tokens[i]);
        }
        i++;
    }

    // 4. Vérifier que la commande est valide
    if (!cmd->name)
    {
        ft_putstr_fd("minishell: syntax error: empty command\n", 2);
        free_cmd(cmd);
        free_tokens(tokens);
        return (NULL);
    }

    free_tokens(tokens);
    return (cmd);
}

int handle_redirection(t_cmd *cmd, char **tokens, int *i)
{
    char    *operator;
    char    *filename;

    operator = tokens[*i];
    (*i)++;

    // Vérifier qu'il y a un fichier après l'opérateur
    if (!tokens[*i])
    {
        ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
        return (0);
    }

    filename = remove_quotes(tokens[*i]);
    if (!filename)
        return (0);

    // Traiter selon le type de redirection
    if (ft_strcmp(operator, "<") == 0)
    {
        free(cmd->input_file);
        cmd->input_file = filename;
    }
    else if (ft_strcmp(operator, ">") == 0)
    {
        free(cmd->output_file);
        cmd->output_file = filename;
        cmd->append = 0;
    }
    else if (ft_strcmp(operator, ">>") == 0)
    {
        free(cmd->output_file);
        cmd->output_file = filename;
        cmd->append = 1;
    }
    else if (ft_strcmp(operator, "<<") == 0)
    {
        free(cmd->heredoc);
        cmd->heredoc = filename;
    }
    else
    {
        free(filename);
        return (0);
    }

    return (1);
}

void add_argument_to_cmd(t_cmd *cmd, char *token)
{
    char    *clean_token;

    clean_token = remove_quotes(token);
    if (!clean_token)
        return;

    // Premier argument = nom de la commande
    if (!cmd->name)
    {
        cmd->name = ft_strdup(clean_token);
    }

    // Ajouter à la liste des arguments
    cmd_add_arg(cmd, ft_strdup(clean_token));

    free(clean_token);
}
```

---

## 2. Exercices Progressifs {#exercices}

### 🎯 Exercice 1 : Shell Basique (Niveau Débutant)

**Objectif :** Créer un shell qui peut exécuter des commandes simples.

```c
// Implémentez cette fonction
int execute_simple_command(char *line)
{
    // TODO:
    // 1. Découper la ligne en mots
    // 2. Le premier mot est la commande
    // 3. Les autres sont les arguments
    // 4. Utiliser fork() et execvp() pour exécuter
    // 5. Attendre la fin avec wait()

    return (0); // Code de retour
}

// Test de l'exercice
int main()
{
    char *line;

    while (1)
    {
        printf("simple_shell> ");
        line = readline("");

        if (!line)
            break;

        if (ft_strcmp(line, "exit") == 0)
            break;

        execute_simple_command(line);
        free(line);
    }

    return (0);
}
```

**Solution suggérée :**
```c
int execute_simple_command(char *line)
{
    char    **args;
    int     pid;
    int     status;

    args = ft_split(line, ' ');
    if (!args || !args[0])
        return (1);

    pid = fork();
    if (pid == 0)
    {
        // Processus enfant
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    }
    else if (pid > 0)
    {
        // Processus parent
        waitpid(pid, &status, 0);
        free_split(args);
        return (WEXITSTATUS(status));
    }
    else
    {
        perror("fork failed");
        free_split(args);
        return (1);
    }
}
```

### 🎯 Exercice 2 : Gestion des Built-ins (Niveau Intermédiaire)

**Objectif :** Ajouter les commandes intégrées cd, pwd, echo.

```c
// Structure pour organiser les built-ins
typedef struct s_builtin
{
    char    *name;
    int     (*function)(char **args);
} t_builtin;

// TODO: Implémentez ces fonctions
int builtin_cd(char **args);
int builtin_pwd(char **args);
int builtin_echo(char **args);

// Tableau des built-ins
t_builtin builtins[] = {
    {"cd", builtin_cd},
    {"pwd", builtin_pwd},
    {"echo", builtin_echo},
    {NULL, NULL}
};

// TODO: Implémentez cette fonction
int is_builtin(char *cmd)
{
    // Vérifier si cmd est dans le tableau builtins
    return (0); // 1 si built-in, 0 sinon
}

int execute_builtin(char **args)
{
    // Trouver et exécuter le built-in
    return (0);
}
```

**Tests :**
```bash
# Dans votre shell
pwd
cd /tmp
pwd
cd ..
echo hello world
echo "quoted string"
```

### 🎯 Exercice 3 : Variables d'Environnement (Niveau Intermédiaire)

**Objectif :** Gérer export, unset, env et l'expansion $VAR.

```c
// TODO: Implémentez ces fonctions

// Initialiser l'environnement depuis envp
t_env *init_environment(char **envp);

// Ajouter/modifier une variable
void set_env_variable(t_env **env, char *key, char *value);

// Supprimer une variable
void unset_env_variable(t_env **env, char *key);

// Obtenir la valeur d'une variable
char *get_env_variable(t_env *env, char *key);

// Expand $VAR dans une chaîne
char *expand_variables(char *str, t_env *env);

// Built-ins pour les variables
int builtin_export(char **args, t_env **env);
int builtin_unset(char **args, t_env **env);
int builtin_env(char **args, t_env *env);
```

**Tests :**
```bash
export TEST=hello
echo $TEST
export PATH="/new/path:$PATH"
echo $PATH
unset TEST
echo $TEST  # Doit être vide
env | grep TEST  # Ne doit rien afficher
```

### 🎯 Exercice 4 : Pipes (Niveau Avancé)

**Objectif :** Implémenter les pipes entre commandes.

```c
// Structure pour une liste de commandes
typedef struct s_pipeline
{
    t_cmd           *cmd;
    struct s_pipeline *next;
} t_pipeline;

// TODO: Implémentez ces fonctions

// Parser une ligne avec pipes
t_pipeline *parse_pipeline(char *line);

// Exécuter un pipeline
int execute_pipeline(t_pipeline *pipeline, t_env **env);

// Configurer les pipes pour un processus enfant
void setup_pipes(t_pipeline *current, int prev_pipe_fd, int next_pipe_fd[2]);
```

**Algorithme suggéré pour les pipes :**
```
Pour chaque commande dans le pipeline:
    1. Si ce n'est pas la dernière commande:
        - Créer un pipe avec pipe()
    2. Fork pour créer un processus enfant
    3. Dans l'enfant:
        - Rediriger stdin vers le pipe précédent (si existe)
        - Rediriger stdout vers le pipe suivant (si existe)
        - Fermer tous les descripteurs de pipe
        - Exécuter la commande
    4. Dans le parent:
        - Fermer les descripteurs appropriés
        - Sauvegarder le pipe pour la commande suivante
    5. Attendre tous les processus enfants
```

**Tests :**
```bash
ls | grep .c
cat /etc/passwd | grep root | wc -l
echo "hello world" | rev | tr 'a-z' 'A-Z'
```

### 🎯 Exercice 5 : Redirections (Niveau Avancé)

**Objectif :** Ajouter >, >>, <, <<.

```c
// TODO: Implémentez ces fonctions

// Gérer les redirections pour une commande
int handle_redirections(t_cmd *cmd);

// Créer un fichier temporaire pour heredoc
int create_heredoc_temp_file(char *delimiter);

// Lire heredoc depuis stdin
int read_heredoc(char *delimiter, int temp_fd);
```

**Tests :**
```bash
echo "test" > output.txt
cat output.txt
echo "append" >> output.txt
cat output.txt
wc -l < output.txt
cat << EOF
ligne 1
ligne 2
EOF
```

---

## 3. Patterns de Programmation {#patterns}

### 🎨 Pattern : Gestionnaire d'Erreurs Centralisé

```c
typedef enum e_error_type
{
    ERROR_MALLOC,
    ERROR_FORK,
    ERROR_PIPE,
    ERROR_SYNTAX,
    ERROR_FILE_NOT_FOUND,
    ERROR_PERMISSION_DENIED
} t_error_type;

void handle_error(t_error_type type, char *context)
{
    switch (type)
    {
        case ERROR_MALLOC:
            ft_putstr_fd("minishell: fatal error: out of memory\n", 2);
            cleanup_and_exit(1);
            break;
        case ERROR_FORK:
            ft_putstr_fd("minishell: fork failed\n", 2);
            break;
        case ERROR_SYNTAX:
            ft_printf("minishell: syntax error near '%s'\n", context);
            break;
        // ... autres cas
    }
}

// Utilisation
if (!malloc_result)
    handle_error(ERROR_MALLOC, NULL);
```

### 🎨 Pattern : Factory pour les Commandes

```c
typedef t_cmd *(*cmd_constructor_t)(char **tokens);

typedef struct s_cmd_factory
{
    char                *type;
    cmd_constructor_t   constructor;
} t_cmd_factory;

t_cmd_factory cmd_factories[] = {
    {"simple", create_simple_cmd},
    {"pipe", create_pipe_cmd},
    {"redirect", create_redirect_cmd},
    {NULL, NULL}
};

t_cmd *create_command(char *type, char **tokens)
{
    int i = 0;

    while (cmd_factories[i].type)
    {
        if (ft_strcmp(cmd_factories[i].type, type) == 0)
            return (cmd_factories[i].constructor(tokens));
        i++;
    }
    return (NULL);
}
```

### 🎨 Pattern : Observer pour les Signaux

```c
typedef void (*signal_handler_t)(int);

typedef struct s_signal_observer
{
    int                         signal;
    signal_handler_t            handler;
    struct s_signal_observer    *next;
} t_signal_observer;

t_signal_observer *g_signal_observers = NULL;

void register_signal_observer(int signal, signal_handler_t handler)
{
    t_signal_observer *new_observer = malloc(sizeof(t_signal_observer));

    new_observer->signal = signal;
    new_observer->handler = handler;
    new_observer->next = g_signal_observers;
    g_signal_observers = new_observer;

    signal(signal, handler);
}

void notify_signal_observers(int signal)
{
    t_signal_observer *current = g_signal_observers;

    while (current)
    {
        if (current->signal == signal)
            current->handler(signal);
        current = current->next;
    }
}
```

---

## 4. Gestion d'Erreurs {#erreurs}

### 🚨 Stratégies de Gestion d'Erreurs

**1. Vérification systématique des allocations :**
```c
void *safe_malloc(size_t size, char *context)
{
    void *ptr = malloc(size);

    if (!ptr)
    {
        ft_printf("minishell: malloc failed in %s\n", context);
        cleanup_and_exit(1);
    }
    return (ptr);
}

char *safe_strdup(char *str, char *context)
{
    char *dup = ft_strdup(str);

    if (!dup)
    {
        ft_printf("minishell: strdup failed in %s\n", context);
        cleanup_and_exit(1);
    }
    return (dup);
}
```

**2. Validation des entrées utilisateur :**
```c
int validate_command_syntax(char *line)
{
    int i = 0;
    int pipe_count = 0;
    int in_quotes = 0;
    char quote_char = 0;

    // Vérifier les pipes en début ou fin
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '|')
        return (syntax_error("unexpected token '|'"));

    // Parcourir la ligne
    while (line[i])
    {
        if (!in_quotes && (line[i] == '\'' || line[i] == '"'))
        {
            in_quotes = 1;
            quote_char = line[i];
        }
        else if (in_quotes && line[i] == quote_char)
        {
            in_quotes = 0;
            quote_char = 0;
        }
        else if (!in_quotes && line[i] == '|')
        {
            pipe_count++;
            // Vérifier qu'il n'y a pas de pipe double
            int j = i + 1;
            while (line[j] == ' ' || line[j] == '\t')
                j++;
            if (line[j] == '|' || !line[j])
                return (syntax_error("unexpected token '|'"));
        }
        i++;
    }

    // Vérifier les quotes non fermées
    if (in_quotes)
        return (syntax_error("unclosed quotes"));

    return (1); // Syntaxe valide
}
```

**3. Récupération d'erreurs gracieuse :**
```c
int execute_with_error_recovery(t_cmd *cmd, t_env **env)
{
    int result;

    // Sauvegarder l'état des descripteurs
    int saved_stdin = dup(0);
    int saved_stdout = dup(1);
    int saved_stderr = dup(2);

    result = execute_command(cmd, env);

    // Restaurer en cas d'erreur
    if (result != 0)
    {
        dup2(saved_stdin, 0);
        dup2(saved_stdout, 1);
        dup2(saved_stderr, 2);
    }

    close(saved_stdin);
    close(saved_stdout);
    close(saved_stderr);

    return (result);
}
```

---

## 5. Optimisations {#optimisations}

### ⚡ Optimisations de Performance

**1. Pool de mémoire pour les allocations fréquentes :**
```c
#define POOL_SIZE 1024
#define BLOCK_SIZE 64

typedef struct s_memory_pool
{
    char    *memory;
    int     *used;
    int     next_free;
} t_memory_pool;

t_memory_pool *init_memory_pool(void)
{
    t_memory_pool *pool = malloc(sizeof(t_memory_pool));

    pool->memory = malloc(POOL_SIZE * BLOCK_SIZE);
    pool->used = calloc(POOL_SIZE, sizeof(int));
    pool->next_free = 0;

    return (pool);
}

void *pool_alloc(t_memory_pool *pool, size_t size)
{
    if (size > BLOCK_SIZE)
        return (malloc(size)); // Fallback pour gros objets

    // Trouver un bloc libre
    for (int i = pool->next_free; i < POOL_SIZE; i++)
    {
        if (!pool->used[i])
        {
            pool->used[i] = 1;
            pool->next_free = i + 1;
            return (pool->memory + i * BLOCK_SIZE);
        }
    }

    return (malloc(size)); // Pool plein, fallback
}

void pool_free(t_memory_pool *pool, void *ptr)
{
    char *char_ptr = (char *)ptr;

    if (char_ptr >= pool->memory &&
        char_ptr < pool->memory + POOL_SIZE * BLOCK_SIZE)
    {
        int index = (char_ptr - pool->memory) / BLOCK_SIZE;
        pool->used[index] = 0;
        if (index < pool->next_free)
            pool->next_free = index;
    }
    else
    {
        free(ptr); // Pas dans le pool
    }
}
```

**2. Cache pour les chemins de commandes :**
```c
typedef struct s_path_cache
{
    char                    *cmd_name;
    char                    *full_path;
    time_t                  cache_time;
    struct s_path_cache     *next;
} t_path_cache;

t_path_cache *g_path_cache = NULL;

char *get_cached_path(char *cmd_name)
{
    t_path_cache *current = g_path_cache;
    time_t now = time(NULL);

    while (current)
    {
        if (ft_strcmp(current->cmd_name, cmd_name) == 0)
        {
            // Vérifier si le cache n'est pas trop ancien (30 secondes)
            if (now - current->cache_time < 30)
                return (ft_strdup(current->full_path));
            else
            {
                // Supprimer l'entrée expirée
                remove_from_cache(current);
                break;
            }
        }
        current = current->next;
    }

    return (NULL); // Pas trouvé ou expiré
}

void add_to_path_cache(char *cmd_name, char *full_path)
{
    t_path_cache *new_entry = malloc(sizeof(t_path_cache));

    new_entry->cmd_name = ft_strdup(cmd_name);
    new_entry->full_path = ft_strdup(full_path);
    new_entry->cache_time = time(NULL);
    new_entry->next = g_path_cache;
    g_path_cache = new_entry;
}
```

**3. Optimisation des expansions de variables :**
```c
// Pré-calculer les expansions communes
typedef struct s_expansion_cache
{
    char                        *pattern;
    char                        *expanded;
    struct s_expansion_cache    *next;
} t_expansion_cache;

char *expand_with_cache(char *str, t_env *env, int last_exit_code)
{
    static t_expansion_cache *cache = NULL;
    t_expansion_cache *current = cache;

    // Chercher dans le cache
    while (current)
    {
        if (ft_strcmp(current->pattern, str) == 0)
            return (ft_strdup(current->expanded));
        current = current->next;
    }

    // Pas trouvé, calculer et mettre en cache
    char *expanded = ft_expand_variables(str, env, last_exit_code);

    // Ajouter au cache (limiter la taille du cache)
    if (count_cache_entries(cache) < 100)
    {
        t_expansion_cache *new_entry = malloc(sizeof(t_expansion_cache));
        new_entry->pattern = ft_strdup(str);
        new_entry->expanded = ft_strdup(expanded);
        new_entry->next = cache;
        cache = new_entry;
    }

    return (expanded);
}
```

### 🧹 Optimisations Mémoire

**1. Libération intelligente :**
```c
void smart_free(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

#define SAFE_FREE(ptr) smart_free((void**)&(ptr))
```

**2. Réutilisation des structures :**
```c
// Pool de structures t_cmd réutilisables
static t_cmd *g_cmd_pool = NULL;

t_cmd *get_cmd_from_pool(void)
{
    if (g_cmd_pool)
    {
        t_cmd *cmd = g_cmd_pool;
        g_cmd_pool = g_cmd_pool->next;

        // Réinitialiser la structure
        ft_memset(cmd, 0, sizeof(t_cmd));
        return (cmd);
    }

    return (malloc(sizeof(t_cmd)));
}

void return_cmd_to_pool(t_cmd *cmd)
{
    if (!cmd)
        return;

    // Nettoyer les données
    SAFE_FREE(cmd->name);
    free_split(cmd->args);
    SAFE_FREE(cmd->input_file);
    SAFE_FREE(cmd->output_file);
    SAFE_FREE(cmd->heredoc);

    // Remettre dans le pool
    cmd->next = g_cmd_pool;
    g_cmd_pool = cmd;
}
```

---

## 🎯 Mini-Projet Final

### 🚀 Défi : Minishell Complet

Créez un minishell qui passe tous ces tests :

```bash
# Test 1 : Commandes simples
echo hello world
ls -la
pwd
whoami

# Test 2 : Built-ins
cd /tmp
pwd
cd -
export TEST=hello
echo $TEST
unset TEST
env | grep TEST

# Test 3 : Pipes
ls | grep .c
cat /etc/passwd | head -5 | tail -1

# Test 4 : Redirections
echo "test" > /tmp/test.txt
cat < /tmp/test.txt
echo "append" >> /tmp/test.txt
cat /tmp/test.txt

# Test 5 : Heredoc
cat << EOF
ligne 1
ligne 2
EOF

# Test 6 : Combinaisons complexes
echo "PATH=$PATH" | grep /usr | wc -l > count.txt

# Test 7 : Gestion d'erreurs
/bin/nonexistent
ls | /bin/nonexistent | wc
> file_without_command

# Test 8 : Signaux
# Ctrl+C pendant une commande
# Ctrl+C au prompt
# Ctrl+D pour quitter

# Test 9 : Quotes et escapes
echo "Hello $USER"
echo 'Hello $USER'
echo "Quote avec \"guillemets\""

# Test 10 : Variables spéciales
echo $?
echo $$
false
echo $?
```

### 📊 Grille d'Évaluation

| Fonctionnalité | Points | Critères |
|----------------|--------|----------|
| Commandes simples | 10 | Exécution correcte, gestion PATH |
| Built-ins | 15 | cd, echo, env, export, unset, pwd, exit |
| Variables | 10 | Expansion $VAR, $?, $$ |
| Pipes | 15 | Pipes multiples, gestion erreurs |
| Redirections | 15 | >, >>, <, << |
| Quotes | 10 | Simple et double quotes |
| Signaux | 10 | Ctrl+C, Ctrl+D, Ctrl+\ |
| Gestion erreurs | 10 | Messages appropriés, codes retour |
| Mémoire | 5 | Pas de fuites (valgrind) |
| **Total** | **100** | |

---

*Bon courage pour votre implémentation ! N'hésitez pas à tester régulièrement et à comparer avec bash. 🐚*
