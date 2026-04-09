/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <ynabti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:58:46 by ynabti            #+#    #+#             */
/*   Updated: 2026/04/08 13:34:38 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_line(char *entry);

static int	env_count(t_list *env)
{
	int	count;

	count = 0;
	while (env && ++count)
		env = env->next;
	return (count);
}

static void	fill_env_array(char **array, t_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		array[i++] = (char *)env->content;
		env = env->next;
	}
	array[i] = NULL;
}

static void	sort_env_array(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_list *env)
{
	char	**array;
	int		size;
	int		i;

	size = env_count(env);
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return ;
	fill_env_array(array, env);
	sort_env_array(array, size);
	i = 0;
	while (i < size)
		print_export_line(array[i++]);
	free(array);
}
