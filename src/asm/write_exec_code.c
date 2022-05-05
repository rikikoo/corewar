/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:44:08 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/05 16:37:08 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_arguments(t_statement *st, int fd)
{
	int			i;
	u_int32_t	val;

	i = 0;
	while (st->argtypes[i])
	{
		if (st->argtypes[i] == T_REG)
		{
			val = ft_atoi(st->arg[i] + 1);
			write(fd, &val, 1);
		}
		i++;
	}
}

// arg type code is 1 byte written so that each argument is 2 bits
// starting from leftmost bits and the last 2 bits are always 00
void	write_argument_type_code(t_statement *st, int fd)
{
	int			i;
	u_int8_t	code;

	i = 0;
	code = 0;
	while (st->argtypes[i])
	{
		if (st->argtypes[i] == T_IND)
			code = code | 0b11 << (6 - 2 * i);
		else
			code = code | st->argtypes[i] << (6 - 2 * i);
		i++;
	}
	write(fd, &code, 1);
}

void	write_statement_code(t_statement *st, int fd)
{
	write(fd, &st->op_code, 1);
}
