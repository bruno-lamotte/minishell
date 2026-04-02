*This project has been created as part of the 42 curriculum by blamotte, ynabti.*

## Description

Minishell is a system programming project focused on reconstructing a POSIX-compliant UNIX shell. At a theoretical level, a shell language is defined as a Type-2 Context-Free Grammar within the [Chomsky hierarchy](https://en.wikipedia.org/wiki/Chomsky_hierarchy), which necessitates a [Pushdown automaton](https://en.wikipedia.org/wiki/Pushdown_automaton) for evaluation. 

To achieve mathematical determinism in syntax validation, this implementation relies on a custom [SLR(1) (Simple LR) parser](https://en.wikipedia.org/wiki/Simple_LR_parser) built entirely from scratch in C, bypassing conventional recursive descent techniques.

### Core Architecture and Parsing Theory

1. **Lexical Analysis & The Lexer Hack**
   The tokenizer parses the input string into discrete symbols. Because shell grammars are inherently ambiguous regarding variable definitions, this engine implements a [Lexer hack](https://en.wikipedia.org/wiki/Lexer_hack). The tokenization phase queries the active state of the SLR(1) parsing table to determine context; it dynamically classifies a string as an `ASSIGNMENT_WORD` (e.g., `PATH=/bin`) or a standard `WORD` strictly based on whether the automaton expects an assignment at that specific node.

2. **Automaton Generation: FIRST Sets & Recursion**
   Building the state machine requires computing FIRST sets (`get_firsts.c`). This involves a deep recursive algorithm. When evaluating a non-terminal symbol that expands into other non-terminals, the function recursively traverses the grammar rules down to the terminal tokens, rigorously managing indirect left-recursion to prevent infinite loops.

3. **Automaton Generation: FOLLOW Sets & Fixed-Point Iteration**
   To resolve when the state machine must combine items into a parent node, it places `REDUCE` actions inside the transition table. These placements are dictated by FOLLOW sets. Because the FOLLOW set of non-terminal $A$ often inherits the FOLLOW set of non-terminal $B$, computing them is a dynamic problem. The system solves this via [Fixed-point iteration](https://en.wikipedia.org/wiki/Fixed-point_iteration) (`get_follows.c`). The algorithm repeatedly sweeps through all grammar rules, continuously propagating symbols across sets. It only terminates when a full pass yields zero modifications—reaching the mathematical fixed point.

4. **The Parsing Table & Determinism**
   The compilation of closures and goto functions generates a static 2D [Parsing table](https://en.wikipedia.org/wiki/LR_parser#Table_construction). During execution, the parser processes tokens purely by performing state lookups (Shift, Reduce, Goto, Accept).
   * **Advantage:** Complete absence of exception handling. The deterministic nature of the finite state machine ensures that any invalid token sequence hits a dead end in the matrix instantly, guaranteeing $O(1)$ syntax error detection per token without complex fallback logic or backtracking.

5. **AST Construction**
   Simultaneous to `REDUCE` operations, the parser dynamically allocates and links an [Abstract Syntax Tree (AST)](https://en.wikipedia.org/wiki/Abstract_syntax_tree), translating the linear tokens into a hierarchical execution structure (commands, pipes, logical sequences, subshells).

## Instructions

**Compilation:**
Execute the following at the root of the repository to build the parser and execution binaries:
```bash
make
```
* `make clean`: Removes intermediate object files.
* `make fclean`: Removes object files and the `minishell` executable.
* `make re`: Clears the build environment and recompiles.

**Execution:**
Initiate the shell process:
```bash
./minishell
```

## Resources

[To be completed]

**AI Usage**
This README.md document, including the theoretical explanations of the SLR(1) parsing mechanics and formatting, was written directly by Gemini based on the provided C codebase and architectural specifications.