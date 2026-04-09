# minishell

Projet realise par `blamotte` et `ynabti` dans le cadre du cursus 42.

## Apercu

`minishell` reproduit le comportement d'un shell UNIX en C.
Le projet combine un parseur maison et un moteur d'execution pour retrouver
le comportement attendu d'un shell interactif dans le cadre du sujet 42.
L'objectif est de proposer un shell stable, lisible et defendable en
soutenance, avec un mandatory solide et les bonus principaux integres.

Fonctionnalites principales :
- prompt interactif et historique
- gestion des quotes simples et doubles
- expansion des variables d'environnement et de `$?`
- redirections `<`, `>`, `<<`, `>>`
- pipes
- builtins `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

Bonus inclus :
- `&&`
- `||`
- parenthèses
- wildcard `*`

Le parsing repose sur un parser `SLR(1)` maison. L'execution est ensuite
separee du parsing, avec une gestion dediee des expansions, des redirections,
des pipes, des builtins et des signaux.

## Structure

Le projet est organise autour de quelques zones principales :
- `src/parsing` pour le tokenizer, le parser et la construction de l'AST
- `src/exec` pour l'expansion, les redirections, les pipes et l'execution
- `src/shell` pour la boucle principale, l'environnement, les heredocs et le terminal
- `src/builtins` pour les builtins du sujet
- `inc` pour les structures et les prototypes

## Build

```bash
make
```

Commandes utiles :
- `make clean`
- `make fclean`
- `make re`

## Execution

```bash
./minishell
```

## Notes

Le projet suit le sujet `minishell` de 42 avec le mandatory et les bonus
principaux. Le parsing, les expansions, les redirections, les pipes et la
gestion des signaux ont ete travailles pour rester stables aussi bien dans
les tests que dans les cas interactifs classiques.

Le projet a ete verifie avec :
- les testeurs communautaires utilises pendant le developpement
- des repros interactifs sur les signaux et les shells imbriques
- des verifications `valgrind` pour la memoire et les file descriptors

## AI Usage

L'IA a ete utilisee de facon pedagogique pendant le projet et pour ecrire ce README.
