/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_INTERNAL_H
# define EXPAND_INTERNAL_H

# include "minishell.h"

# define PROTECTED_CHAR '\1'
# define LITERAL_STAR '\2'

typedef struct s_expand_buf
{
	char	*buf;
	size_t	len;
	size_t	cap;
}	t_expand_buf;

typedef struct s_encode_ctx
{
	char			*str;
	int				i;
	int				keep_empty;
	t_shell			*shell;
	t_expand_buf	out;
}	t_encode_ctx;

int		grow_expand_buffer(t_expand_buf *buf, size_t need);
int		expand_buf_char(t_expand_buf *buf, char c);
int		expand_buf_text(t_expand_buf *buf, char *text);
int		expand_buf_protected(t_expand_buf *buf, char c);
int		expand_buf_string(t_expand_buf *buf, char *str, int protect);

char	*expand_var_value(char *str, int *i, t_shell *shell);
int		parse_single_quote(t_encode_ctx *ctx);
int		parse_double_quote(t_encode_ctx *ctx);
char	*encode_word(char *str, t_shell *shell, int *keep_empty);

char	*strip_protected(char *encoded);
char	*wildcard_pattern(char *encoded);
int		has_raw_wildcard(char *encoded);
char	*encoded_slice(char *encoded, int start, int end);
int		add_field(t_list **fields, char *encoded);
int		split_fields(char *encoded, int keep_empty, t_list **fields);
char	**expand_fields_to_array(t_list **fields, int count);
int		add_plain_field(t_list **plain_fields, char *plain);
int		add_wildcard_matches(t_list **plain_fields, char **matches, int count);

#endif
