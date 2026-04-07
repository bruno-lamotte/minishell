/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by user              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_rules_part_0(t_reduce_rule *rules)
{
	rules[1].left_symbol = "complete_command";
	rules[1].nb_items = 1;
	rules[2].left_symbol = "list";
	rules[2].nb_items = 1;
	rules[3].left_symbol = "list";
	rules[3].nb_items = 3;
	rules[4].left_symbol = "list";
	rules[4].nb_items = 3;
	rules[5].left_symbol = "list";
	rules[5].nb_items = 2;
	rules[6].left_symbol = "and_or";
	rules[6].nb_items = 1;
	rules[7].left_symbol = "and_or";
	rules[7].nb_items = 3;
	rules[8].left_symbol = "and_or";
	rules[8].nb_items = 3;
	rules[9].left_symbol = "pipeline";
	rules[9].nb_items = 1;
	rules[10].left_symbol = "pipeline";
	rules[10].nb_items = 3;
	rules[11].left_symbol = "pipeline";
	rules[11].nb_items = 2;
	rules[12].left_symbol = "command";
	rules[12].nb_items = 1;
	init_rules_part_1(rules);
}

void	init_rules_part_1(t_reduce_rule *rules)
{
	rules[13].left_symbol = "command";
	rules[13].nb_items = 1;
	rules[14].left_symbol = "command";
	rules[14].nb_items = 2;
	rules[15].left_symbol = "subshell";
	rules[15].nb_items = 3;
	rules[16].left_symbol = "simple_command";
	rules[16].nb_items = 3;
	rules[17].left_symbol = "simple_command";
	rules[17].nb_items = 2;
	rules[18].left_symbol = "simple_command";
	rules[18].nb_items = 1;
	rules[19].left_symbol = "simple_command";
	rules[19].nb_items = 2;
	rules[20].left_symbol = "simple_command";
	rules[20].nb_items = 1;
	rules[21].left_symbol = "cmd_name";
	rules[21].nb_items = 1;
	rules[22].left_symbol = "cmd_word";
	rules[22].nb_items = 1;
	rules[23].left_symbol = "cmd_prefix";
	rules[23].nb_items = 1;
	rules[24].left_symbol = "cmd_prefix";
	rules[24].nb_items = 2;
	init_rules_part_2(rules);
}

void	init_rules_part_2(t_reduce_rule *rules)
{
	rules[25].left_symbol = "cmd_prefix";
	rules[25].nb_items = 1;
	rules[26].left_symbol = "cmd_prefix";
	rules[26].nb_items = 2;
	rules[27].left_symbol = "cmd_suffix";
	rules[27].nb_items = 1;
	rules[28].left_symbol = "cmd_suffix";
	rules[28].nb_items = 2;
	rules[29].left_symbol = "cmd_suffix";
	rules[29].nb_items = 1;
	rules[30].left_symbol = "cmd_suffix";
	rules[30].nb_items = 2;
	rules[31].left_symbol = "redirect_list";
	rules[31].nb_items = 1;
	rules[32].left_symbol = "redirect_list";
	rules[32].nb_items = 2;
	rules[33].left_symbol = "io_redirect";
	rules[33].nb_items = 1;
	rules[34].left_symbol = "io_redirect";
	rules[34].nb_items = 1;
	rules[35].left_symbol = "io_file";
	rules[35].nb_items = 2;
	rules[36].left_symbol = "io_file";
	rules[36].nb_items = 2;
	init_rules_part_3(rules);
}

void	init_rules_part_3(t_reduce_rule *rules)
{
	rules[37].left_symbol = "io_file";
	rules[37].nb_items = 2;
	rules[38].left_symbol = "io_file";
	rules[38].nb_items = 2;
	rules[39].left_symbol = "io_file";
	rules[39].nb_items = 2;
	rules[40].left_symbol = "filename";
	rules[40].nb_items = 1;
	rules[41].left_symbol = "io_here";
	rules[41].nb_items = 2;
	rules[42].left_symbol = "here_end";
	rules[42].nb_items = 1;
}
