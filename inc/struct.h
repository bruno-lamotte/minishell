#ifndef STRUCT_H
# define STRUCT_H


# include <minishell.h>

typedef struct      s_token
{
    int             type;
    char            *value;
}                   t_token;

typedef struct      s_rule
{
    int             id;
    char            *left_vars;
    t_list          *right_vars;
    int             nb_items;
    struct s_rule   *next_rule;

}                   t_rule;

typedef struct      s_item
{
    int             id;
    t_rule          *rule_of_item;
    int             dot_pos;
    struct s_item   *next_item;
}                   t_item;

typedef struct      s_symbol
{
    char            *name;
    t_list          *firsts;
    t_list          *sfollows;
    struct s_symbol    *next_symbol;
}                   t_symbol;

typedef struct      s_state
{
    int             id;
    t_list          *items;
    t_list          *transitions;
    struct s_state  *next_state;
}                   t_state;

typedef struct      s_transition
{
    char            *symbol;
    struct s_state  *dest_state;
}                   t_transition;

#endif