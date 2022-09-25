/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:53:32 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/25 17:54:03 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "oplist.h"

void	save_label(char *label, t_statement *cur, int cur_size)
{
	t_label	*tmp;

	append_labels(&cur->label);
	tmp = cur->label;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->label = label;
	tmp->pos = cur_size;
}

// saves to struct the operation's code, whether argument type code
// is needed, and T_DIR size
void	assign_op_specs(t_data *data, t_statement *st)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(st->op_name, g_oplist[i].op_name))
		{
			st->op_code = g_oplist[i].op_code;
			st->arg_type_code = g_oplist[i].arg_type_code;
			st->t_dir_size = g_oplist[i].t_dir_size;
			return ;
		}
		i++;
	}
	parser_error_exit("invalid operation name", data->row, data->col + 1);
}

int	is_label_char(char s)
{
	size_t	i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (s == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}
