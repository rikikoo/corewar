/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:52:35 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/25 18:02:14 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "oplist.h"

void	validate_arg_amount(t_data *data, t_statement *cur)
{
	if (cur->arg[(int)g_oplist[cur->op_code - 1].arg_cnt - 1] == NULL)
		parser_error_exit("too few arguments", data->row, data->col);
}

// validates that the statement's operation accepts certain type of
// argument at certain argument number
void	validate_arg_type(t_data *data, t_statement *cur, int arg_num,
int arg_type)
{
	if ((int)g_oplist[cur->op_code - 1].arg_type[arg_num] != \
	(int)(g_oplist[cur->op_code - 1].arg_type[arg_num] | arg_type))
		parser_error_exit("invalid argument type", data->row, data->col + 1);
}

void	validate_arg_end(t_data *data, char *s)
{
	skip_whitespace(s, &data->col);
	if (s[data->col] != '\0' && s[data->col] != SEPARATOR_CHAR)
		parser_error_exit("invalid argument", data->row, data->col + 1);
}
