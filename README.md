# 🐚 Minishell - Shell Unix Simplifié

Un shell Unix fonctionnel développé en C, implémentant les fonctionnalités essentielles de bash pour le projet 42.

## 📋 Description

Minishell est un interpréteur de commandes qui reproduit le comportement de bash pour les fonctionnalités obligatoires. Ce projet permet de comprendre en profondeur le fonctionnement des shells Unix, la gestion des processus, et la programmation système.

## ✨ Fonctionnalités

### 🔧 Commandes Built-in
- `cd` - Changer de répertoire (avec gestion relative/absolue et `~`)
- `echo` - Afficher du texte (avec option `-n`)
- `pwd` - Afficher le répertoire courant
- `export` - Gérer les variables d'environnement
- `unset` - Supprimer des variables d'environnement
- `env` - Afficher l'environnement
- `exit` - Quitter le shell (avec codes de retour)

### 🚀 Fonctionnalités Avancées
- **Variables d'environnement** : expansion `$VAR`, `$HOME`, `$USER`, etc.
- **Pipes** : `cmd1 | cmd2 | cmd3`
- **Redirections** : `>`, `>>`, `<`, `<<` (heredoc)
- **Gestion des signaux** : `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- **Historique des commandes** : navigation avec ↑/↓
- **Gestion des quotes** : `"double quotes"` et `'single quotes'`
- **Variable spéciale** : `$?` (code de retour de la dernière commande)

### 🎯 Conformité
- Comportement identique à bash pour les fonctionnalités implémentées
- Gestion complète des erreurs avec messages appropriés
- Aucune fuite mémoire (testé avec Valgrind)
- Respect de la Norme 42

## 🛠️ Installation et Compilation

### Prérequis
```bash
# Sur Ubuntu/Debian
sudo apt install build-essential libreadline-dev

# Sur macOS (avec Homebrew)
brew install readline
```

### Compilation
```bash
# Cloner le projet
git clone <repository-url>
cd minishell

# Compiler
make

# Nettoyer les fichiers objets
make clean

# Nettoyer complètement
make fclean

# Recompiler
make re
```

## 🚀 Utilisation

```bash
# Lancer le shell
./minishell

# Exemples d'utilisation
minishell> echo "Hello World!"
minishell> export MY_VAR=42
minishell> echo $MY_VAR
minishell> ls -la | grep .c | wc -l
minishell> cat << EOF
> Ceci est un heredoc
> EOF
minishell> exit
```

## 🧪 Tests

```bash
# Tests de base
./minishell
ls
pwd
echo $HOME
cd /tmp && pwd

# Tests avec pipes
echo "test" | cat | wc -w
ls | grep main | head -5

# Tests avec redirections
echo "Hello" > test.txt
cat < test.txt
cat << EOF > file.txt
Ligne 1
Ligne 2
EOF

# Tests des built-ins
export TEST=hello
echo $TEST
unset TEST
echo $TEST
```

## 📚 Documentation et Cours

Ce projet est accompagné d'une documentation pédagogique complète pour comprendre les concepts et apprendre à développer un shell Unix :

### 📖 Cours Théoriques

- **[COURS_MINISHELL.md](./docs/COURS_MINISHELL.md)** - Cours théorique complet
  - Architecture d'un shell Unix
  - Concepts système (processus, descripteurs, signaux)
  - Patterns de programmation avancés
  - Guide de compilation et tests
  - Section détaillée sur les processus Unix (fork, exec, wait, pipes)

- **[GUIDE_DEBUTANT.md](./docs/GUIDE_DEBUTANT.md)** - Guide pas-à-pas pour débutants
  - Introduction progressive aux concepts
  - Étapes de développement détaillées
  - Exemples de code commentés
  - Quiz et exercices pratiques
  - Explication complète des processus Unix avec schémas

### 💻 Exemples Pratiques

- **[EXEMPLES_EXERCICES.md](./docs/EXEMPLES_EXERCICES.md)** - Exemples de code et exercices
  - Implémentations détaillées de chaque fonctionnalité
  - Exercices progressifs avec solutions
  - Patterns avancés et optimisations
  - Techniques de débogage

### 🎯 Pour Qui ?

- **Étudiants 42** : comprendre le projet minishell
- **Débutants en système** : apprendre la programmation Unix
- **Développeurs** : réviser les concepts de shells et processus

## 📁 Structure du Projet

```
minishell/
├── main.c                    # Point d'entrée du programme
├── Makefile                  # Système de build
├── include/
│   ├── minishell.h          # Header principal
│   └── libft/               # Bibliothèque utilitaire
├── src/
│   ├── builtins/            # Commandes intégrées
│   │   ├── cd/              # Implémentation de cd
│   │   ├── echo/            # Implémentation de echo
│   │   ├── env/             # Gestion environnement
│   │   ├── export/          # Export de variables
│   │   ├── pwd/             # Répertoire courant
│   │   └── unset/           # Suppression variables
│   ├── exec/                # Moteur d'exécution
│   ├── parsing/             # Analyseur syntaxique
│   ├── signals/             # Gestion des signaux
│   └── utils/               # Utilitaires divers
├── obj/                     # Fichiers objets (généré)
└── docs/                    # 📚 Documentation pédagogique
    ├── COURS_MINISHELL.md   # 📖 Cours théorique complet
    ├── GUIDE_DEBUTANT.md    # 🎓 Guide pas-à-pas débutant
    └── EXEMPLES_EXERCICES.md # 💻 Exemples et exercices
```

## 🔧 Débogage

### Outils Recommandés
```bash
# Compilation avec debug
make CFLAGS="-Wall -Wextra -Werror -g"

# Débogage avec GDB
gdb ./minishell

# Détection des fuites mémoire
valgrind --leak-check=full ./minishell

# Analyse statique
cppcheck src/
```

### Logs et Traces
```bash
# Activer les traces (si implémenté)
export MINISHELL_DEBUG=1
./minishell

# Tester avec différents shells
bash -c "commande"    # Comportement attendu
./minishell           # Votre implémentation
```

## 📊 Performance et Optimisation

- **Gestion mémoire** : Allocation/libération optimisée
- **Processus** : Fork minimal, exec efficace
- **Parsing** : Analyse en une passe
- **Variables** : Table de hachage pour l'environnement

## 🤝 Contribution

### Standards de Code
- Respect de la Norme 42
- Commentaires en français ou anglais
- Tests unitaires pour les nouvelles fonctionnalités
- Pas de fuites mémoire

### Tests Avant Soumission
```bash
# Tests obligatoires
make && ./minishell
valgrind --leak-check=full ./minishell
norminette src/ include/

# Tests de régression
bash test_script.sh
```

## 📝 Notes de Développement

### Commandes Testées
- Toutes les commandes de base Unix
- Combinaisons complexes avec pipes et redirections
- Gestion des erreurs et cas limites
- Compatibilité avec les scripts bash simples

### Limitations Connues
- Pas de support pour les fonctions bash
- Pas de support pour les expressions arithmétiques
- Pas de support pour les boucles (for, while)
- Job control limité

## 📄 Licence

Ce projet est développé dans le cadre de la formation 42. Consultez les règles de l'école concernant la réutilisation du code.

## 🙏 Remerciements

- **École 42** pour le sujet du projet
- **Communauté 42** pour les tests et retours
- **Créateurs de bash** pour l'inspiration
- **Documentation Unix** pour les spécifications

---

**Développé avec ❤️ pour comprendre les shells Unix**

*Pour toute question ou suggestion, consultez la documentation pédagogique incluse !*
