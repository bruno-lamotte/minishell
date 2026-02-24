/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 02:48:29 by blamotte          #+#    #+#             */
/*   Updated: 2025/12/04 02:48:33 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef struct s_data
{
	va_list	args;
	int		width;
	int		precision;
	int		zero;
	int		point;
	int		dash;
	int		len;
	int		plus;
	int		space;
	int		hash;
	char	buffer[BUFFER_SIZE];
	int		index_buffer;
}			t_data;

void		ft_putchar_buffer(char c, t_data *list);
void		ft_putstr_buffer(char *str, t_data *list);
void		ft_flush(t_data *list);
size_t		ft_strlen(const char *s);
const char	*parsing_s(const char *s, t_data *list);
void		ft_print_nb_base(unsigned long long n, char *base, char *prefix,
				t_data *list);
void		ft_print_int(t_data *list);
void		ft_print_unsigned(t_data *list);
void		ft_print_hex(t_data *list, char type);
void		ft_print_ptr(t_data *list);
void		ft_print_char(t_data *list);
void		ft_print_str(t_data *list);
void		ft_print_percent(t_data *list);
int			ft_printf(const char *s, ...);
int			ft_nbrlen_base(unsigned long long n, int base_len);
void		ft_putnbr_recursive(unsigned long long n, char *base, t_data *list);
void		ft_put_n_char(int len, char c, t_data *list);
void		ft_print_nb_base(unsigned long long n, char *base, char *prefix,
				t_data *list);
void		ft_print_spaces(int len, t_data *list);
const char	*parsing_flags(const char *s, t_data *list);
const char	*parsing_width(const char *s, t_data *list);
const char	*parsing_precision(const char *s, t_data *list);

#endif
