/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:50:05 by blamotte          #+#    #+#             */
/*   Updated: 2026/03/01 19:11:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_leftsymbol_from_grammar(t_parser *data, t_rule **new_rule,
		char *line)
{
	int	i;

	i = 0;
	if (line[i] == ' ')
		(*new_rule)->left_symbol = ft_strdup(ft_lstlast(data->rules)->left_symbol);
	else
	{
		while (line[i] != ' ' && line[i] != ':')
			i++;
		(*new_rule)->left_symbol = ft_substr(line, 0, i);
	}
}

void	get_id_from_grammar(t_parser *data, t_rule **new_rule, char *line)
{
	(*new_rule)->id = (ft_lstlast(data->rules)->content->id + 1);
}

void	get_rightsymbols_from_grammar(t_parser *data, t_rule **new_rule,
		char *line)
{
	int		i;
	char	*symbol;
	t_list	*new_list;

	while (line)
	{
		i = 0;
		while (*line == ' ')
			line++;
		while (line[i] != ' ' || line[i] != '\n')
			i++;
		symbol = ft_substr(line, 0, i);
		new_list = ft_lstnew(symbol);
		ft_lstadd_back(&(*new_rule)->right_symbols, new_list);
		line += i;
	}
}

void	get_nbitems_from_grammar(t_parser *data, t_rule **new_rule, char *line)
{
	int	i;
	t_list	*tmp;
	
	tmp = (*new_rule)->right_symbols;
	i = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	(*new_rule)->nb_items = i;
}

void	get_rule_from_grammar(t_parser *data, t_rule **new_rule, char *line)
{
	int	i;

	i = 0;
	get_id_from_grammar(data, new_rule, line);
	get_leftsymbol_from_grammar(data, new_rule, line);
	while (*line != '|' && *line != ':')
		line++;
	get_rightsymbols_from_grammar(data, new_rule, line);
	get_nbitems_from_grammar(data, new_rule, line);
}
int	parse_grammar(t_parser *data)
{
	int		fd;
	int		i;
	char	*line;
	t_rule	*new_rule;
	t_list	*new_list;

	fd = open(grammar.txt, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (*line == "\n")
			break ;
		new_rule = malloc(sizeof(t_rule));
		if (!new_rule)
			return (0);
		get_rule_from_grammar(data, &new_rule, line);
		new_list = ft_lstnew(new_rule);
		ft_lstadd_back(&data->rules, new_list);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}
