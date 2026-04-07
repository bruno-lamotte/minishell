/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_symbols_part_0(char **symbols)
{
	symbols[0] = "$";
	symbols[1] = "complete_command";
	symbols[2] = "list";
	symbols[3] = "and_or";
	symbols[4] = "SEMI";
	symbols[5] = "BACKGROUND";
	symbols[6] = "pipeline";
	symbols[7] = "AND_IF";
	symbols[8] = "OR_IF";
	symbols[9] = "command";
	symbols[10] = "PIPE";
	symbols[11] = "BANG";
	symbols[12] = "simple_command";
	symbols[13] = "subshell";
	symbols[14] = "redirect_list";
	symbols[15] = "L_PAREN";
	symbols[16] = "R_PAREN";
	symbols[17] = "cmd_prefix";
	symbols[18] = "cmd_word";
	symbols[19] = "cmd_suffix";
	symbols[20] = "cmd_name";
	symbols[21] = "WORD";
	symbols[22] = "io_redirect";
	symbols[23] = "ASSIGNMENT_WORD";
	init_symbols_part_1(symbols);
}

void	init_symbols_part_1(char **symbols)
{
	symbols[24] = "io_file";
	symbols[25] = "io_here";
	symbols[26] = "LESS";
	symbols[27] = "filename";
	symbols[28] = "GREAT";
	symbols[29] = "DGREAT";
	symbols[30] = "LESSGREAT";
	symbols[31] = "ANDGREAT";
	symbols[32] = "DLESS";
	symbols[33] = "here_end";
	symbols[34] = NULL;
}
