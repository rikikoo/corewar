/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:11:40 by vhallama          #+#    #+#             */
/*   Updated: 2022/08/30 19:49:07 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "oplist.h"

// If statement has no code, i.e. only label, label points to
// byte after champ exec code and thus this function returns 0
static u_int32_t	get_operation_bytesize(t_statement *st)
{
	u_int32_t	ret;
	int			i;

	if (!st->op_code)
		return (0);
	ret = 1;
	if (st->arg_type_code)
		ret++;
	i = 0;
	while (st->argtypes[i])
	{
		if (st->argtypes[i] == T_REG)
			ret++;
		else if (st->argtypes[i] == T_DIR)
			ret += st->t_dir_size;
		else
			ret += 2;
		i++;
	}
	return (ret);
}

// saves label positions according to current size of champ exec code
// as it is calculated statement by statement
void	save_label_positions(t_statement *st, u_int32_t cur_size)
{
	t_label	*cur;

	cur = st->label;
	while (cur != NULL)
	{
		cur->pos = cur_size;
		cur = cur->next;
	}
}

// calculates statement sizes and saves where labels point to
// and the total champ exec code size
void	analyze_size_and_labels(t_data *data, t_statement *st)
{
	while (st != NULL)
	{
		save_label_positions(st, data->champ_size);
		data->champ_size += get_operation_bytesize(st);
		st = st->next;
	}
	if (data->champ_size > CHAMP_MAX_SIZE)
		error_exit("Error: champion exec code size too large");
}
