*This project has been created as part of the 42 curriculum by blamotte, ynabti.*

# minishell

## Description

`minishell` is a small UNIX shell written in C for the 42 curriculum.
The goal of the project is to reproduce the core behavior of a Bourne-like
shell with a strong focus on processes, pipes, redirections, signals, and
environment handling.

This implementation includes:
- an interactive prompt with history
- quote handling for single and double quotes
- environment expansion, including `$?`
- redirections `<`, `>`, `<<`, `>>`
- pipelines
- the mandatory builtins `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

The project also includes the main bonus features used in our repository:
- logical operators `&&` and `||`
- subshells with parentheses
- wildcard expansion with `*`

The parser is based on a custom `SLR(1)` approach, while execution is handled
separately through dedicated runtime code for expansion, redirections, pipes,
builtins, and signals.

## Instructions

Build the project from the repository root:

```bash
make
```

Useful rules:
- `make clean`
- `make fclean`
- `make re`
- `make bonus`

Run the shell with:

```bash
./minishell
```

Project layout:
- `src/parsing` contains tokenization, parser logic, and AST construction
- `src/exec` contains expansion, redirections, pipes, and command execution
- `src/shell` contains the shell loop, environment helpers, heredocs, and terminal handling
- `src/builtins` contains builtin commands
- `inc` contains shared structures and prototypes

## Resources

Classic references used for the project:
- GNU Bash Manual: https://www.gnu.org/software/bash/manual/bash.html
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- GNU Readline Manual: https://tiswww.case.edu/php/chet/readline/rltop.html
- Linux `signal(7)`, `pipe(2)`, `dup(2)`, `waitpid(2)`, `execve(2)` man pages

AI was used in a pedagogical way during the project to discuss ideas, review
behaviors, and help structure explanations. AI was also used to write this
`README.md`.
