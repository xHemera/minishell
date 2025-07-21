# 🎓 Guide Pas-à-Pas : Construire son Premier Minishell

## 📚 Prérequis et Introduction

### 🎯 Qu'allons-nous Apprendre ?
Ce guide vous accompagne dans la création d'un shell Unix fonctionnel, étape par étape, en expliquant chaque concept.

### 📋 Ce que vous devez savoir avant de commencer
- **Langage C** : pointeurs, structures, allocation dynamique
- **Système Unix** : processus, descripteurs de fichiers
- **Compilation** : gcc, Makefile

### 🛠️ Outils nécessaires
- Compilateur gcc
- Librairie readline (`sudo apt install libreadline-dev`)
- Debugger gdb (optionnel mais recommandé)
- Valgrind pour détecter les fuites mémoire

---

## 🔄 Comprendre les Processus Unix - Théorie Essentielle

### 🎯 Qu'est-ce qu'un Processus ?

> **📖 Définition**
>
> Un **processus** est un programme en cours d'exécution. Chaque processus a :
> - Un **PID** (Process ID) unique
> - Sa propre **mémoire** isolée
> - Ses propres **descripteurs de fichiers**
> - Un **répertoire de travail**
> - Des **variables d'environnement**

### 🌳 Hiérarchie des Processus

```
systemd (PID 1)
├── bash (PID 1234)
│   ├── minishell (PID 5678)
│   │   ├── ls (PID 9101)
│   │   └── grep (PID 9102)
│   └── firefox (PID 2345)
└── other processes...
```

> **💡 Point Clé**
>
> Chaque processus a un **parent** (sauf le processus initial). Le shell est le parent des commandes qu'il lance.

### 🔧 Les Appels Système Fondamentaux

#### 1. `fork()` - Créer un Processus

```c
#include <unistd.h>

int main(void)
{
    int pid;

    printf("Avant fork - PID: %d\n", getpid());

    pid = fork();

    if (pid == 0)
    {
        // Code du processus ENFANT
        printf("Je suis l'enfant - PID: %d, Parent: %d\n",
               getpid(), getppid());
    }
    else if (pid > 0)
    {
        // Code du processus PARENT
        printf("Je suis le parent - PID: %d, Enfant créé: %d\n",
               getpid(), pid);
    }
    else
    {
        // Erreur
        perror("fork failed");
        return (1);
    }

    printf("Cette ligne s'affiche dans les DEUX processus!\n");
    return (0);
}
```

**Sortie exemple :**
```
Avant fork - PID: 1234
Je suis le parent - PID: 1234, Enfant créé: 5678
Je suis l'enfant - PID: 5678, Parent: 1234
Cette ligne s'affiche dans les DEUX processus!
Cette ligne s'affiche dans les DEUX processus!
```

> **⚠️ Important**
>
> Après `fork()`, il y a **DEUX** processus identiques qui exécutent le même code !
> - Dans le **parent** : `fork()` retourne le PID de l'enfant
> - Dans l'**enfant** : `fork()` retourne 0
> - En cas d'**erreur** : `fork()` retourne -1

#### 2. `exec()` - Remplacer un Programme

```c
#include <unistd.h>

int main(void)
{
    char *args[] = {"ls", "-l", NULL};

    printf("Avant exec - PID: %d\n", getpid());

    // Remplacer ce programme par 'ls -l'
    execvp("ls", args);

    // Cette ligne ne s'exécutera JAMAIS si exec réussit
    printf("Erreur: exec a échoué!\n");
    return (1);
}
```

> **📖 Concept**
>
> `exec()` **remplace complètement** le programme actuel par un autre.
> - Le PID reste le même
> - La mémoire est entièrement remplacée
> - Si `exec()` réussit, le code après n'est jamais exécuté

#### 3. `wait()` - Attendre un Processus Enfant

```c
#include <sys/wait.h>

int main(void)
{
    int pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // Enfant : faire quelque chose puis terminer
        printf("Enfant travaille...\n");
        sleep(2);
        printf("Enfant terminé\n");
        exit(42); // Code de retour
    }
    else if (pid > 0)
    {
        // Parent : attendre l'enfant
        printf("Parent attend...\n");
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            printf("Enfant terminé avec code: %d\n", WEXITSTATUS(status));
    }

    return (0);
}
```

### 🎯 Pattern Classique : Fork + Exec + Wait

```c
int execute_program(char *program, char **args)
{
    int pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // ENFANT : exécuter le programme
        execvp(program, args);

        // Si on arrive ici, exec a échoué
        perror("exec failed");
        exit(127);
    }
    else if (pid > 0)
    {
        // PARENT : attendre la fin
        waitpid(pid, &status, 0);
        return (WEXITSTATUS(status));
    }
    else
    {
        // ERREUR
        perror("fork failed");
        return (-1);
    }
}
```

### 🔍 Exercice Pratique : Mini-Lanceur

**Créez ce programme pour comprendre :**

```c
// mini_launcher.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    char command[256];
    char *args[10];
    int pid, status;

    while (1)
    {
        printf("launcher> ");

        // Lire la commande
        if (!fgets(command, sizeof(command), stdin))
            break;

        // Supprimer le \n
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0)
            break;

        // Simple : juste le nom du programme
        args[0] = command;
        args[1] = NULL;

        // Fork + Exec + Wait
        pid = fork();
        if (pid == 0)
        {
            execvp(command, args);
            printf("Commande non trouvée: %s\n", command);
            exit(1);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
            printf("Terminé avec code: %d\n", WEXITSTATUS(status));
        }
        else
        {
            perror("fork");
        }
    }

    return (0);
}
```

**Testez :**
```bash
gcc mini_launcher.c -o mini_launcher
./mini_launcher
launcher> ls
launcher> pwd
launcher> date
launcher> exit
```

### 🌊 Comprendre les Descripteurs de Fichiers

> **📖 Concept**
>
> Chaque processus a des **descripteurs de fichiers** :
> - **0** : stdin (entrée standard)
> - **1** : stdout (sortie standard)
> - **2** : stderr (erreur standard)

```c
#include <unistd.h>

int main(void)
{
    // Écrire sur stdout (descripteur 1)
    write(1, "Hello stdout\n", 13);

    // Écrire sur stderr (descripteur 2)
    write(2, "Hello stderr\n", 13);

    return (0);
}
```

### 🔗 Les Pipes - Communication Inter-Processus

```c
#include <unistd.h>

int main(void)
{
    int pipe_fd[2];
    int pid;
    char buffer[100];

    // Créer un pipe
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (1);
    }

    pid = fork();

    if (pid == 0)
    {
        // ENFANT : écrire dans le pipe
        close(pipe_fd[0]); // Fermer lecture

        write(pipe_fd[1], "Message de l'enfant", 19);
        close(pipe_fd[1]);
        exit(0);
    }
    else if (pid > 0)
    {
        // PARENT : lire du pipe
        close(pipe_fd[1]); // Fermer écriture

        int bytes = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        buffer[bytes] = '\0';

        printf("Reçu: %s\n", buffer);
        close(pipe_fd[0]);

        wait(NULL);
    }

    return (0);
}
```

### 🎯 Redirection avec `dup2()`

```c
#include <fcntl.h>

int main(void)
{
    int fd;

    // Ouvrir un fichier
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Rediriger stdout vers le fichier
    dup2(fd, 1);
    close(fd);

    // Maintenant printf écrit dans le fichier !
    printf("Cette ligne va dans output.txt\n");

    return (0);
}
```

### 🔄 Variables d'Environnement et Processus

```c
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
    // Afficher l'environnement
    for (int i = 0; envp[i]; i++)
        printf("%s\n", envp[i]);

    // Modifier l'environnement (pour ce processus seulement)
    setenv("MA_VARIABLE", "ma_valeur", 1);

    // Les processus enfants héritent de l'environnement modifié
    if (fork() == 0)
    {
        printf("Dans l'enfant: MA_VARIABLE = %s\n", getenv("MA_VARIABLE"));
        exit(0);
    }

    wait(NULL);
    return (0);
}
```

### 📊 Schéma Récapitulatif : Shell et Processus

```
SHELL (processus parent)
│
├── fork() ──→ PROCESSUS ENFANT
│               │
│               ├── dup2() pour redirections
│               ├── exec("ls")
│               └── exit(code)
│
├── wait() ←── récupère le code de retour
│
└── continue la boucle...
```

### ✅ Quiz de Compréhension

**1. Que se passe-t-il après ce code ?**
```c
if (fork() == 0)
    printf("A\n");
else
    printf("B\n");
printf("C\n");
```

<details>
<summary>Réponse</summary>
Sortie : "A\nC\nB\nC\n" (ordre peut varier)
- L'enfant affiche A puis C
- Le parent affiche B puis C
</details>

**2. Pourquoi `cd` doit être un built-in ?**

<details>
<summary>Réponse</summary>
Si `cd` était un programme externe :
1. Le shell ferait fork()
2. L'enfant changerait de répertoire
3. L'enfant mourrait
4. Le shell parent resterait dans l'ancien répertoire
</details>

**3. Comment créer un pipe `cmd1 | cmd2` ?**

<details>
<summary>Réponse</summary>
1. Créer un pipe avec pipe()
2. Fork pour cmd1 : rediriger stdout vers pipe[1]
3. Fork pour cmd2 : rediriger stdin depuis pipe[0]
4. Fermer tous les descripteurs dans le parent
5. Attendre les deux enfants
</details>

---

## 📍 Étape 1 : Structure de Base et Première Boucle

### 🎯 Objectif
Créer un programme qui affiche un prompt et lit des commandes.

### 📁 Créer l'arborescence
```bash
mkdir minishell
cd minishell
mkdir src include obj
touch main.c include/minishell.h Makefile
```

### 📝 Header minimal (include/minishell.h)
```c
#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes standard */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Prototypes */
void	minishell_loop(void);

#endif
```

### 🔧 Premier main.c
```c
#include "include/minishell.h"

int main(void)
{
	printf("🐚 Bienvenue dans votre premier minishell!\n");
	printf("Tapez 'exit' pour quitter.\n\n");

	minishell_loop();

	printf("Au revoir!\n");
	return (0);
}

void minishell_loop(void)
{
	char *line;

	while (1)
	{
		// Afficher le prompt et lire la ligne
		line = readline("minishell> ");

		// Ctrl+D (EOF) = quitter
		if (!line)
		{
			printf("\n");
			break;
		}

		// Commande vide = ignorer
		if (!*line)
		{
			free(line);
			continue;
		}

		// Commande exit = quitter
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		// Pour l'instant, juste afficher ce qui a été tapé
		printf("Vous avez tapé: '%s'\n", line);

		// Ajouter à l'historique
		add_history(line);

		// Libérer la mémoire
		free(line);
	}
}
```

### 🔨 Makefile simple
```makefile
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -lreadline

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

### ✅ Test de l'étape 1
```bash
make
./minishell
# Testez: tapez quelques mots, exit, Ctrl+D
```

**🎉 Félicitations !** Vous avez un shell qui lit des commandes !

---

## 📍 Étape 2 : Exécution de Commandes Simples

### 🎯 Objectif
Faire exécuter de vraies commandes Unix comme `ls`, `pwd`, `whoami`.

### 📚 Concepts à comprendre

> **📖 Théorie : Fork et Exec**
> - `fork()` crée une copie du processus actuel
> - Dans le **processus parent** : `fork()` retourne le PID de l'enfant
> - Dans le **processus enfant** : `fork()` retourne 0
> - `execvp()` remplace le programme du processus par un autre
> - `wait()` fait attendre le parent que l'enfant termine

### 🔧 Ajout au header
```c
// Dans include/minishell.h, ajoutez :
# include <sys/wait.h>

/* Nouvelles fonctions */
char	**ft_split(char const *s, char c);
void	free_split(char **split);
int		execute_command(char **args);
```

### 🛠️ Implémentation de ft_split (ajoutez à la fin de main.c)
```c
// Fonction utilitaire pour compter les mots
static int count_words(char const *s, char c)
{
	int count = 0;
	int in_word = 0;

	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

// Fonction utilitaire pour extraire un mot
static char *extract_word(char const *s, char c, int *start)
{
	int end = *start;
	char *word;
	int len;

	// Trouver la fin du mot
	while (s[end] && s[end] != c)
		end++;

	len = end - *start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);

	// Copier le mot
	for (int i = 0; i < len; i++)
		word[i] = s[*start + i];
	word[len] = '\0';

	*start = end;
	return (word);
}

// Découper une chaîne selon un délimiteur
char **ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);

	int word_count = count_words(s, c);
	char **result = malloc(sizeof(char*) * (word_count + 1));
	if (!result)
		return (NULL);

	int i = 0;
	int pos = 0;

	while (i < word_count)
	{
		// Ignorer les délimiteurs
		while (s[pos] == c)
			pos++;

		// Extraire le mot
		result[i] = extract_word(s, c, &pos);
		if (!result[i])
		{
			// Erreur d'allocation, nettoyer
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}

	result[word_count] = NULL;
	return (result);
}

// Libérer un tableau de chaînes
void free_split(char **split)
{
	if (!split)
		return;

	for (int i = 0; split[i]; i++)
		free(split[i]);
	free(split);
}
```

### 🚀 Fonction d'exécution
```c
// Ajouter à main.c
int execute_command(char **args)
{
	if (!args || !args[0])
		return (1);

	int pid = fork();

	if (pid == 0)
	{
		// Dans le processus enfant
		// execvp cherche le programme dans PATH
		if (execvp(args[0], args) == -1)
		{
			printf("minishell: %s: command not found\n", args[0]);
			exit(127); // Code d'erreur standard pour "command not found"
		}
	}
	else if (pid > 0)
	{
		// Dans le processus parent
		int status;
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		// Erreur de fork
		perror("fork");
		return (1);
	}

	return (0);
}
```

### 🔄 Mise à jour de la boucle principale
```c
// Remplacer la fonction minishell_loop dans main.c
void minishell_loop(void)
{
	char *line;
	char **args;

	while (1)
	{
		line = readline("minishell> ");

		if (!line) // Ctrl+D
		{
			printf("\n");
			break;
		}

		if (!*line) // Ligne vide
		{
			free(line);
			continue;
		}

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		// Découper la ligne en arguments
		args = ft_split(line, ' ');
		if (args)
		{
			execute_command(args);
			free_split(args);
		}

		add_history(line);
		free(line);
	}
}
```

### ✅ Test de l'étape 2
```bash
make re
./minishell
# Testez : ls, pwd, whoami, date, echo hello
```

**🎉 Bravo !** Votre shell peut maintenant exécuter des commandes !

---

## 📍 Étape 3 : Première Commande Built-in (cd)

### 🎯 Objectif
Implémenter la commande `cd` qui doit changer le répertoire du shell lui-même.

### 📚 Pourquoi cd doit être built-in ?

> **📖 Théorie**
> `cd` doit être implémenté dans le shell car :
> - `fork()` crée un processus séparé
> - Changer de répertoire dans l'enfant n'affecte pas le parent
> - Le shell doit changer SON propre répertoire de travail

### 🔧 Ajout au header
```c
// Dans include/minishell.h, ajoutez :
int		is_builtin(char *cmd);
int		execute_builtin(char **args);
int		builtin_cd(char **args);
```

### 🛠️ Implémentation des built-ins
```c
// Ajouter à main.c

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);

	if (strcmp(cmd, "cd") == 0)
		return (1);
	// On ajoutera d'autres built-ins plus tard

	return (0);
}

int builtin_cd(char **args)
{
	char *path;

	// cd sans argument = aller au HOME
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	else
	{
		path = args[1];
	}

	// Changer de répertoire
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}

	return (0);
}

int execute_builtin(char **args)
{
	if (strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));

	return (1); // Built-in non trouvé
}
```

### 🔄 Mise à jour de l'exécution
```c
// Modifier execute_command dans main.c
int execute_command(char **args)
{
	if (!args || !args[0])
		return (1);

	// Vérifier si c'est un built-in
	if (is_builtin(args[0]))
		return (execute_builtin(args));

	// Sinon, exécution normale
	int pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			printf("minishell: %s: command not found\n", args[0]);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		return (1);
	}

	return (0);
}
```

### ✅ Test de l'étape 3
```bash
make re
./minishell
pwd          # Noter le répertoire
cd /tmp
pwd          # Doit afficher /tmp
cd           # Retour au HOME
pwd          # Doit afficher votre répertoire home
cd /invalid  # Doit afficher une erreur
```

**🎉 Excellent !** Votre shell gère maintenant sa première commande intégrée !

---

## 📍 Étape 4 : Variables d'Environnement Basiques

### 🎯 Objectif
Gérer les variables d'environnement et implémenter `echo`, `env`, `export`.

### 📚 Structure pour l'environnement

```c
// Ajouter à include/minishell.h
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

/* Nouvelles fonctions */
t_env	*init_env(char **envp);
char	*get_env_value(t_env *env, char *key);
void	set_env_value(t_env **env, char *key, char *value);
void	free_env(t_env *env);
int		builtin_echo(char **args);
int		builtin_env(char **args, t_env *env);
int		builtin_export(char **args, t_env **env);

/* Variable globale pour l'environnement */
extern t_env *g_env;
```

### 🛠️ Gestion de l'environnement
```c
// Ajouter à main.c
t_env *g_env = NULL;

t_env *init_env(char **envp)
{
	t_env *env = NULL;
	t_env *new_var;
	char *equal_pos;
	int i = 0;

	while (envp[i])
	{
		equal_pos = strchr(envp[i], '=');
		if (equal_pos)
		{
			new_var = malloc(sizeof(t_env));
			if (!new_var)
				return (NULL);

			// Extraire la clé
			int key_len = equal_pos - envp[i];
			new_var->key = malloc(key_len + 1);
			strncpy(new_var->key, envp[i], key_len);
			new_var->key[key_len] = '\0';

			// Extraire la valeur
			new_var->value = malloc(strlen(equal_pos + 1) + 1);
			strcpy(new_var->value, equal_pos + 1);

			// Ajouter en tête de liste
			new_var->next = env;
			env = new_var;
		}
		i++;
	}

	return (env);
}

char *get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void set_env_value(t_env **env, char *key, char *value)
{
	t_env *current = *env;

	// Chercher si la variable existe déjà
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = malloc(strlen(value) + 1);
			strcpy(current->value, value);
			return;
		}
		current = current->next;
	}

	// Variable n'existe pas, la créer
	t_env *new_var = malloc(sizeof(t_env));
	new_var->key = malloc(strlen(key) + 1);
	strcpy(new_var->key, key);
	new_var->value = malloc(strlen(value) + 1);
	strcpy(new_var->value, value);
	new_var->next = *env;
	*env = new_var;
}

void free_env(t_env *env)
{
	t_env *temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}
```

### 🎯 Nouveaux built-ins
```c
// Ajouter à main.c

int builtin_echo(char **args)
{
	int i = 1;
	int newline = 1;

	// Vérifier l'option -n
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	// Afficher les arguments
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (0);
}

int builtin_env(char **args, t_env *env)
{
	(void)args; // Ignorer les arguments pour simplifier

	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}

	return (0);
}

int builtin_export(char **args, t_env **env)
{
	char *equal_pos;
	char *key;
	char *value;
	int i = 1;

	if (!args[1])
	{
		// export sans arguments = afficher toutes les variables
		return (builtin_env(args, *env));
	}

	// Traiter chaque argument
	while (args[i])
	{
		equal_pos = strchr(args[i], '=');
		if (equal_pos)
		{
			// Format: KEY=VALUE
			int key_len = equal_pos - args[i];
			key = malloc(key_len + 1);
			strncpy(key, args[i], key_len);
			key[key_len] = '\0';

			value = equal_pos + 1;
			set_env_value(env, key, value);

			free(key);
		}
		else
		{
			// Format: KEY (sans valeur)
			set_env_value(env, args[i], "");
		}
		i++;
	}

	return (0);
}
```

### 🔄 Mise à jour des fonctions
```c
// Modifier is_builtin
int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);

	if (strcmp(cmd, "cd") == 0 ||
		strcmp(cmd, "echo") == 0 ||
		strcmp(cmd, "env") == 0 ||
		strcmp(cmd, "export") == 0)
		return (1);

	return (0);
}

// Modifier execute_builtin
int execute_builtin(char **args)
{
	if (strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	else if (strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (strcmp(args[0], "env") == 0)
		return (builtin_env(args, g_env));
	else if (strcmp(args[0], "export") == 0)
		return (builtin_export(args, &g_env));

	return (1);
}

// Modifier main pour initialiser l'environnement
int main(void)
{
	extern char **environ;

	printf("🐚 Bienvenue dans votre minishell!\n");

	// Initialiser l'environnement
	g_env = init_env(environ);
	if (!g_env)
	{
		printf("Erreur: impossible d'initialiser l'environnement\n");
		return (1);
	}

	minishell_loop();

	// Nettoyer
	free_env(g_env);
	printf("Au revoir!\n");
	return (0);
}
```

### ✅ Test de l'étape 4
```bash
make re
./minishell
echo hello world
echo -n "sans retour à la ligne"
env | grep HOME
export TEST=hello
env | grep TEST
echo $TEST   # Ne marchera pas encore (expansion variables)
```

**🎉 Formidable !** Votre shell gère maintenant l'environnement !

---

## 📍 Étape 5 : Expansion de Variables ($VAR)

### 🎯 Objectif
Faire en sorte que `echo $HOME` affiche le contenu de la variable HOME.

### 🔧 Ajout au header
```c
// Dans include/minishell.h
char	*expand_variables(char *str, t_env *env);
```

### 🛠️ Fonction d'expansion
```c
// Ajouter à main.c

char *expand_variables(char *str, t_env *env)
{
	if (!str)
		return (NULL);

	// Calculer la taille nécessaire
	int len = strlen(str);
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '$' && str[i + 1])
		{
			// Trouver la fin de la variable
			int start = i + 1;
			int end = start;
			while (str[end] && (str[end] == '_' ||
				(str[end] >= 'a' && str[end] <= 'z') ||
				(str[end] >= 'A' && str[end] <= 'Z') ||
				(str[end] >= '0' && str[end] <= '9')))
				end++;

			if (end > start)
			{
				// Extraire le nom de la variable
				char *var_name = malloc(end - start + 1);
				strncpy(var_name, str + start, end - start);
				var_name[end - start] = '\0';

				// Chercher sa valeur
				char *value = get_env_value(env, var_name);
				if (value)
				{
					len += strlen(value) - (end - i);
				}
				else
				{
					len -= (end - i); // Variable non trouvée = supprimée
				}

				free(var_name);
				i = end - 1; // -1 car la boucle va incrémenter
			}
		}
	}

	// Allouer la nouvelle chaîne
	char *result = malloc(len + 1);
	if (!result)
		return (NULL);

	// Construire la chaîne avec expansion
	int j = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '$' && str[i + 1])
		{
			int start = i + 1;
			int end = start;
			while (str[end] && (str[end] == '_' ||
				(str[end] >= 'a' && str[end] <= 'z') ||
				(str[end] >= 'A' && str[end] <= 'Z') ||
				(str[end] >= '0' && str[end] <= '9')))
				end++;

			if (end > start)
			{
				char *var_name = malloc(end - start + 1);
				strncpy(var_name, str + start, end - start);
				var_name[end - start] = '\0';

				char *value = get_env_value(env, var_name);
				if (value)
				{
					strcpy(result + j, value);
					j += strlen(value);
				}

				free(var_name);
				i = end - 1;
			}
			else
			{
				result[j++] = str[i]; // Juste un '$' isolé
			}
		}
		else
		{
			result[j++] = str[i];
		}
	}

	result[j] = '\0';
	return (result);
}
```

### 🔄 Mise à jour de l'exécution
```c
// Modifier minishell_loop pour expanser les variables
void minishell_loop(void)
{
	char *line;
	char *expanded_line;
	char **args;

	while (1)
	{
		line = readline("minishell> ");

		if (!line)
		{
			printf("\n");
			break;
		}

		if (!*line)
		{
			free(line);
			continue;
		}

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		// Expanser les variables
		expanded_line = expand_variables(line, g_env);
		if (!expanded_line)
			expanded_line = line; // En cas d'erreur, utiliser l'original

		args = ft_split(expanded_line, ' ');
		if (args)
		{
			execute_command(args);
			free_split(args);
		}

		add_history(line);

		if (expanded_line != line)
			free(expanded_line);
		free(line);
	}
}
```

### ✅ Test de l'étape 5
```bash
make re
./minishell
export TEST=hello
echo $TEST        # Doit afficher "hello"
echo $HOME        # Doit afficher votre répertoire home
echo $USER        # Doit afficher votre nom d'utilisateur
echo $NONEXISTENT # Ne doit rien afficher
```

**🎉 Fantastique !** Votre shell gère maintenant l'expansion de variables !

---

## 📍 Étape 6 : Premier Pipe Simple

### 🎯 Objectif
Faire fonctionner `echo hello | cat` et autres pipes simples.

### 📚 Théorie des Pipes

> **📖 Concept**
> Un pipe connecte la sortie (stdout) d'un processus à l'entrée (stdin) d'un autre :
> ```
> Processus A --[stdout]--> PIPE --[stdin]--> Processus B
> ```

### 🔧 Ajout au header
```c
// Dans include/minishell.h
typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
} t_cmd;

t_cmd	*parse_pipeline(char *line);
int		execute_pipeline(t_cmd *cmd_list);
void	free_cmd_list(t_cmd *cmd_list);
```

### 🛠️ Structure pour les pipelines
```c
// Ajouter à main.c

t_cmd *create_cmd(char **args)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	cmd->args = args;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *parse_pipeline(char *line)
{
	t_cmd *first_cmd = NULL;
	t_cmd *current_cmd = NULL;
	char *pipe_pos;
	char *segment;
	char **args;

	while ((pipe_pos = strchr(line, '|')) != NULL)
	{
		// Extraire le segment avant le pipe
		int segment_len = pipe_pos - line;
		segment = malloc(segment_len + 1);
		strncpy(segment, line, segment_len);
		segment[segment_len] = '\0';

		// Supprimer les espaces en début/fin
		// (version simplifiée, vous pouvez améliorer)
		while (*segment == ' ')
			segment++;

		// Tokeniser le segment
		args = ft_split(segment, ' ');
		if (args)
		{
			t_cmd *new_cmd = create_cmd(args);
			if (!first_cmd)
			{
				first_cmd = new_cmd;
				current_cmd = new_cmd;
			}
			else
			{
				current_cmd->next = new_cmd;
				current_cmd = new_cmd;
			}
		}

		free(segment);
		line = pipe_pos + 1; // Passer au segment suivant
	}

	// Traiter le dernier segment (après le dernier pipe)
	while (*line == ' ')
		line++;

	if (*line)
	{
		args = ft_split(line, ' ');
		if (args)
		{
			t_cmd *new_cmd = create_cmd(args);
			if (!first_cmd)
			{
				first_cmd = new_cmd;
			}
			else
			{
				current_cmd->next = new_cmd;
			}
		}
	}

	return (first_cmd);
}

int execute_pipeline(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (1);

	// Cas simple : une seule commande (pas de pipe)
	if (!cmd_list->next)
		return (execute_command(cmd_list->args));

	// Pipeline avec au moins 2 commandes
	t_cmd *current = cmd_list;
	int pipe_fd[2];
	int input_fd = 0; // stdin du premier processus
	int pid;

	while (current)
	{
		// Créer un pipe si ce n'est pas la dernière commande
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}

		pid = fork();
		if (pid == 0)
		{
			// Processus enfant

			// Rediriger l'entrée si nécessaire
			if (input_fd != 0)
			{
				dup2(input_fd, 0);
				close(input_fd);
			}

			// Rediriger la sortie si ce n'est pas la dernière commande
			if (current->next)
			{
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}

			// Exécuter la commande
			if (is_builtin(current->args[0]))
			{
				exit(execute_builtin(current->args));
			}
			else
			{
				execvp(current->args[0], current->args);
				printf("minishell: %s: command not found\n", current->args[0]);
				exit(127);
			}
		}
		else if (pid > 0)
		{
			// Processus parent

			// Fermer l'ancienne entrée
			if (input_fd != 0)
				close(input_fd);

			// Fermer l'écriture du pipe actuel
			if (current->next)
			{
				close(pipe_fd[1]);
				input_fd = pipe_fd[0]; // Cette sortie devient l'entrée suivante
			}
		}
		else
		{
			perror("fork");
			return (1);
		}

		current = current->next;
	}

	// Attendre tous les processus enfants
	int status;
	while (wait(&status) > 0)
		;

	return (WEXITSTATUS(status));
}

void free_cmd_list(t_cmd *cmd_list)
{
	t_cmd *temp;

	while (cmd_list)
	{
		temp = cmd_list->next;
		free_split(cmd_list->args);
		free(cmd_list);
		cmd_list = temp;
	}
}
```

### 🔄 Mise à jour de la boucle principale
```c
// Modifier minishell_loop
void minishell_loop(void)
{
	char *line;
	char *expanded_line;
	t_cmd *cmd_list;

	while (1)
	{
		line = readline("minishell> ");

		if (!line)
		{
			printf("\n");
			break;
		}

		if (!*line)
		{
			free(line);
			continue;
		}

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		// Expanser les variables
		expanded_line = expand_variables(line, g_env);
		if (!expanded_line)
			expanded_line = line;

		// Vérifier s'il y a des pipes
		if (strchr(expanded_line, '|'))
		{
			cmd_list = parse_pipeline(expanded_line);
			if (cmd_list)
			{
				execute_pipeline(cmd_list);
				free_cmd_list(cmd_list);
			}
		}
		else
		{
			// Commande simple (ancien code)
			char **args = ft_split(expanded_line, ' ');
			if (args)
			{
				execute_command(args);
				free_split(args);
			}
		}

		add_history(line);

		if (expanded_line != line)
			free(expanded_line);
		free(line);
	}
}
```

### ✅ Test de l'étape 6
```bash
make re
./minishell
echo hello | cat
ls | grep main
echo "test pipe" | wc -w
echo $USER | cat
```

**🎉 Incroyable !** Votre shell peut maintenant gérer les pipes !

---

## 📍 Étape 7 : Gestion des Signaux (Ctrl+C)

### 🎯 Objectif
Faire en sorte que Ctrl+C interrompe la commande courante mais pas le shell.

### 📚 Concept des Signaux

> **📖 Théorie**
> - **SIGINT** : signal envoyé par Ctrl+C
> - **SIGQUIT** : signal envoyé par Ctrl+\
> - Le shell doit capturer ces signaux différemment des commandes

### 🔧 Ajout au header
```c
// Dans include/minishell.h
# include <signal.h>

void	setup_signals(void);
void	handle_sigint(int sig);
```

### 🛠️ Gestion des signaux
```c
// Ajouter à main.c

void handle_sigint(int sig)
{
	(void)sig;

	// Afficher une nouvelle ligne
	write(1, "\n", 1);

	// Réafficher le prompt
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void setup_signals(void)
{
	// Capturer Ctrl+C
	signal(SIGINT, handle_sigint);

	// Ignorer Ctrl+backslash
	signal(SIGQUIT, SIG_IGN);
}

void setup_signals_child(void)
{
	// Dans les processus enfants, comportement par défaut
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
```

### 🔄 Mise à jour de l'exécution
```c
// Modifier execute_command pour configurer les signaux dans l'enfant
int execute_command(char **args)
{
	if (!args || !args[0])
		return (1);

	if (is_builtin(args[0]))
		return (execute_builtin(args));

	int pid = fork();

	if (pid == 0)
	{
		// Configurer les signaux pour l'enfant
		setup_signals_child();

		if (execvp(args[0], args) == -1)
		{
			printf("minishell: %s: command not found\n", args[0]);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		return (1);
	}

	return (0);
}

// Modifier main pour configurer les signaux
int main(void)
{
	extern char **environ;

	printf("🐚 Bienvenue dans votre minishell!\n");
	printf("Testez Ctrl+C pendant une commande ou au prompt!\n\n");

	// Configurer les signaux
	setup_signals();

	g_env = init_env(environ);
	if (!g_env)
	{
		printf("Erreur: impossible d'initialiser l'environnement\n");
		return (1);
	}

	minishell_loop();

	free_env(g_env);
	printf("Au revoir!\n");
	return (0);
}
```

### ✅ Test de l'étape 7
```bash
make re
./minishell
sleep 5    # Tapez Ctrl+C pendant l'exécution
# Le sleep doit s'arrêter, mais le shell doit continuer
# Tapez Ctrl+C au prompt -> nouvelle ligne, nouveau prompt
```

**🎉 Parfait !** Votre shell gère maintenant les signaux correctement !

---

## 🎊 Félicitations !

### 🏆 Ce que vous avez accompli

Vous avez créé un minishell fonctionnel qui peut :

✅ **Exécuter des commandes** : `ls`, `pwd`, `whoami`, etc.
✅ **Gérer les built-ins** : `cd`, `echo`, `env`, `export`
✅ **Expanser les variables** : `echo $HOME`, `echo $USER`
✅ **Utiliser les pipes** : `ls | grep .c`
✅ **Gérer les signaux** : Ctrl+C interrompt les commandes mais pas le shell

### 🚀 Prochaines Étapes (Fonctionnalités Avancées)

1. **Redirections** : `>`, `>>`, `<`, `<<`
2. **Gestion des quotes** : `echo "hello world"`, `echo 'no expansion'`
3. **Plus de built-ins** : `pwd`, `unset`, `exit` avec codes de retour
4. **Gestion d'erreurs** : messages d'erreur comme bash
5. **Variables spéciales** : `$?` (code de retour), `$$` (PID)
6. **Heredoc** : `cat << EOF`

### 📚 Pour Aller Plus Loin

**Livres recommandés :**
- "Advanced Programming in the Unix Environment" - Stevens
- "The Linux Programming Interface" - Kerrisk

**Documentation :**
- `man bash` : manuel complet de bash
- `man 2 fork`, `man 2 execve`, `man 2 pipe` : appels système
- `man 3 readline` : bibliothèque readline

### 🔧 Conseils pour Continuer

1. **Testez régulièrement** avec différentes commandes
2. **Comparez avec bash** : comment bash gère-t-il telle situation ?
3. **Utilisez valgrind** pour détecter les fuites mémoire
4. **Documentez votre code** pour vous y retrouver plus tard
5. **Implémentez une fonctionnalité à la fois** et testez-la complètement

### 🐛 Débogage

Si quelque chose ne fonctionne pas :

1. **Compilez avec `-g`** pour le debug
2. **Utilisez `gdb`** : `gdb ./minishell`
3. **Ajoutez des `printf`** pour tracer l'exécution
4. **Vérifiez avec `valgrind`** : `valgrind ./minishell`

---

**🎉 Bravo ! Vous avez créé votre premier shell Unix !**

*Continuez à expérimenter et à améliorer votre code. La programmation système est un domaine passionnant qui vous ouvrira de nombreuses portes ! 🚪✨*
