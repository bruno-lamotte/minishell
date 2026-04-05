/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>             +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:22:07 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/04 19:35:41 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(t_shell *shell, char *name, int len)
{
	t_list	*cur;
	char	*content;

	cur = shell->env;
	while (cur)
	{
		content = (char *)cur->content;
		if (ft_strncmp(content, name, len) == 0 && content[len] == '=')
			return (content + len + 1);
		cur = cur->next;
	}
	return (NULL);
}

static char	*expand_var(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_code));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	name = ft_substr(str, start, *i - start);
	val = get_env_val(shell, name, *i - start);
	free(name);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

static char	*expand_dquote(char *str, int *i, t_shell *shell)
{
	char	*res;
	char	*tmp;
	char	*part;

	res = ft_strdup("");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			part = expand_var(str, i, shell);
		else
		{
			part = ft_substr(str, *i, 1);
			(*i)++;
		}
		tmp = ft_strjoin(res, part);
		free(res);
		free(part);
		res = tmp;
	}
	if (str[*i] == '"')
		(*i)++;
	return (res);
}

char	*expand_str(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp;
	char	*part;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			part = ft_strdup("");
			while (str[i] && str[i] != '\'')
			{
				tmp = ft_strjoin(part, ft_substr(str, i, 1));
				free(part);
				part = tmp;
				i++;
			}
			if (str[i])
				i++;
		}
		else if (str[i] == '"')
			part = expand_dquote(str, &i, shell);
		else if (str[i] == '$')
			part = expand_var(str, &i, shell);
		else
		{
			part = ft_substr(str, i, 1);
			i++;
		}
		tmp = ft_strjoin(res, part);
		free(res);
		free(part);
		res = tmp;
	}
	return (res);
}

char	**expand_args(char **args, t_shell *shell)
{
	char	**expanded;
	int		n;
	int		i;

	n = 0;
	while (args[n])
		n++;
	expanded = malloc(sizeof(char *) * (n + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	while (i < n)
	{
		expanded[i] = expand_str(args[i], shell);
		i++;
	}
	expanded[n] = NULL;
	return (expanded);
}
