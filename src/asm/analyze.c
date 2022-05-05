/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:11:40 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/05 13:24:51 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "oplist.h"

static u_int32_t	get_operation_bytesize(t_statement *st)
{
	u_int32_t	ret;
	int			i;

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

void	analyze(t_data *data, t_statement *st)
{
	while (st != NULL)
	{
		st->pos = data->champ_size;
		data->champ_size += get_operation_bytesize(st);
		st = st->next;
	}
	if (data->champ_size > CHAMP_MAX_SIZE) // DOES ASM CARE?
		error_exit("Error: champion exec code size too large");
}
