
void    complete_symbol_datas(t_parser data, t_symbol symbol, char *name)
{
    symbol->name = ft_strdup(name);
    if (!symbol->name)
        return (/*a completer*/);
    get_firsts(data, &symbol);
    get_
}

int symbol_already_parsed(t_list symbols, char *left_symbol)
{
    while (data->symbols)
		{
			if (ft_strcmp(data->symbols->content->name,
					data->rules->content->left_symbol))
                return (1);
			else
				data->symbols = data->symbols->next;
		}
    return (0);
}

void	get_symbols_from_rules(t_parser data)
{
	t_symbol	*new_symbol;
    t_list      *new_list;

	while (data->rules)
	{
		if (!symbol_already_parsed(data->symbols, data->rules->content->left_symbol))
		{
			new_symbol = malloc(sizeof(t_symbol));
			if (!new_symbol)
				return (/*error jsp*/);
            complete_symbol_datas(data, &new_symbol, data->rules->content->left_symbol);
            new_list = ft_lstnew(new_symbol);
            if (!new_list)
                return (/*je ne sais tjrs pas*/);
            ft_lstadd_back(&data->symbol, new_list);
		}
	}
}
