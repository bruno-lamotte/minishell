/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 21:41:13 by marvin            #+#    #+#             */
/*   Updated: 2026/04/05 21:41:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_chunk(char *res, char *str, int start, int end)
{
	char	*chunk;
	char	*new_res;

	if (start == end)
		return (res);
	chunk = ft_substr(str, start, end - start);
	new_res = ft_strjoin(res, chunk);
	free(res);
	free(chunk);
	return (new_res);
}

char	*get_env_val(char *name, t_shell *shell)
{
	t_list	*node;
	char	*content;
	char	*eq;

	if (!ft_strcmp(name, "?"))
		return (ft_itoa(shell->exit_code));
	node = find_var(shell->env, name);
	if (!node || !node->content)
		return (ft_strdup(""));
	content = (char *)node->content;
	eq = ft_strchr(content, '=');
	if (eq)
		return (ft_strdup(eq + 1));
	return (ft_strdup(""));
}

char	*append_var(char *res, char *str, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*val;
	char	*new_res;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
		(*i)++;
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
	name = ft_substr(str, start, *i - start);
	val = get_env_val(name, shell);
	new_res = ft_strjoin(res, val);
	free(res);
	free(name);
	free(val);
	return (new_res);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*res;
	int		i;
	int		start;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			res = append_chunk(res, str, start, i);
			res = append_var(res, str, &i, shell);
			start = i;
		}
		else
			i++;
	}
	return (append_chunk(res, str, start, i));
}
