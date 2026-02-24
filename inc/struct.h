#ifndef STRUCT_H
# define STRUCT_H


# include <minishell.h>

typedef struct      s_token
{
    int             type;
    char            *value;
}                   t_token;