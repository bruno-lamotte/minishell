/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:16:57 by blamotte          #+#    #+#             */
/*   Updated: 2026/01/20 08:22:54 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_MAX
#  define FD_MAX 6
# endif

typedef struct s_global
{
	char			content[BUFFER_SIZE];
	ssize_t			siz;
	struct s_global	*next;
}					t_global;

char				*get_next_line(int fd);
void				ft_clear(t_global **stash);
int					is_eol(t_global *list);
int					line_size(t_global *lst);

#endif
