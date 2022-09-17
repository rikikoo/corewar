/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:44:08 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/17 15:22:19 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// if t_ind is label, find label start byte position, then
// calculate distance from label start byte to operation start byte
// then for all values change value to big endian.
// write value in 2 bytes.
static void	write_t_ind(t_statement **head, t_statement *st, int i, int fd)
{
	char		*match;
	u_int16_t	val;

	if (st->arg[i][0] == LABEL_CHAR)
	{
		match = st->arg[i] + 1;
		val = find_label_pos(head, match);
		val -= st->pos;
	}
	else
		val = ft_atoi(st->arg[i]);
	val = u_int16_to_big_endian(val);
	write(fd, &val, 2);
}

// if t_dir is label, first find label start byte position, then
// calculate distance from label start byte to operation start byte
// then for all values change value to big endian.
// if t_dir_size is 2, make a bit shift and write t_dir_size many bytes
static void	write_t_dir(t_statement **head, t_statement *st, int i, int fd)
{
	char		*match;
	u_int32_t	val;

	if (st->arg[i][1] == LABEL_CHAR)
	{
		match = st->arg[i] + 2;
		val = find_label_pos(head, match);
		val -= st->pos;
	}
	else
		val = ft_atoi(st->arg[i] + 1);
	val = u_int32_to_big_endian(val);
	if (st->t_dir_size == 2)
		val = val >> 16;
	write(fd, &val, st->t_dir_size);
}

void	write_arguments(t_statement **head, t_statement *st, int fd)
{
	int			i;
	u_int8_t	val;

	i = 0;
	while (i < 3 && st->argtypes[i])
	{
		if (st->argtypes[i] == T_REG)
		{
			val = ft_atoi(st->arg[i] + 1);
			write(fd, &val, 1);
		}
		else if (st->argtypes[i] == T_DIR)
			write_t_dir(head, st, i, fd);
		else
			write_t_ind(head, st, i, fd);
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
	while (i < 3 && st->argtypes[i])
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
