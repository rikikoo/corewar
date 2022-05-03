/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:53:32 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 13:17:42 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "oplist.h"

u_int8_t	assign_op_code(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(s, g_oplist[i].op_name))
			return (g_oplist[i].op_code);
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
