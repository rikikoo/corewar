/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:21:28 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/23 20:22:44 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** returns the size of an argument in bytes. T_DIR size depends on @inst_code.
*/
int	get_arg_size(int inst_code, int arg)
{
	if (arg == REG_CODE)
		return (REG_CODE);
	else if (arg == IND_CODE)
		return (IND_SIZE);
	else if (arg == DIR_CODE)
	{
		if ((inst_code >= 10 && inst_code <= 12) || inst_code >= 14)
			return (IND_SIZE);
		else
			return (DIR_SIZE);
	}
	else
		return (0);
}

int	get_reg_no(t_inst instruct, unsigned char *arena, int pos, int arg)
{
	int	v;

	if (arg == 1)
		v = arena[(pos + 2) % MEM_SIZE];
	else if (arg == 2)
		v = arena[(pos + 2 + instruct.sizes[0]) % MEM_SIZE];
	else if (arg == 3)
		v = arena[(pos + 2 + instruct.sizes[0] + instruct.sizes[1]) % MEM_SIZE];
	else
		v = 0;
	return (v);
}

/*
** stores the values of the first two instruction arguments (or last two if
** inst_code == 11, i.e. sti) into @vals.
** called by bitwise instructions (6, 7, 8) and ldi, sti, lldi (10, 11, 14).
*/
void	get_inst_operands(
	t_inst instruct,
	unsigned char *arena,
	t_car *car,
	int *vals)
{
	int		arg_idx;

	arg_idx = 0 + (instruct.inst_code == 11);
	if (instruct.types[arg_idx] != REG_CODE && \
	instruct.sizes[arg_idx] == IND_SIZE)
		vals[0] = get_ind_val(instruct, arena, car, arg_idx + 1) % IDX_MOD;
	else
		vals[0] = get_arg_val(instruct, arena, car, arg_idx + 1);
	if (instruct.types[arg_idx + 1] != REG_CODE && \
	instruct.sizes[arg_idx + 1] == IND_SIZE)
		vals[1] = get_ind_val(instruct, arena, car, arg_idx + 2) % IDX_MOD;
	else
		vals[1] = get_arg_val(instruct, arena, car, arg_idx + 2);
}

short	get_ind_val(t_inst instruct, unsigned char *arena, t_car *car, int arg)
{
	int		pos;
	short	val;

	if (arg == 1)
		pos = (car->pos + 2) % MEM_SIZE;
	else if (arg == 2)
		pos = (car->pos + 2 + instruct.sizes[0]) % MEM_SIZE;
	else
		pos = (car->pos + 2 + instruct.sizes[0] + instruct.sizes[1]) % MEM_SIZE;
	val = (arena[pos] << 8) + arena[(pos + 1) % MEM_SIZE];
	return (val);
}

int	get_arg_val(t_inst instruct, unsigned char *arena, t_car *car, int arg)
{
	int	pos;

	if (arg == 1)
		pos = (car->pos + 2) % MEM_SIZE;
	else if (arg == 2)
		pos = (car->pos + 2 + instruct.sizes[0]) % MEM_SIZE;
	else
		pos = (car->pos + 2 + instruct.sizes[0] + instruct.sizes[1]) % MEM_SIZE;
	if (instruct.types[arg - 1] == DIR_CODE)
		return (n_bytes_to_int(arena, pos, instruct.sizes[arg - 1]));
	else if (instruct.types[arg - 1] == REG_CODE)
	{
		if (arena[pos] > 0 && arena[pos] <= REG_NUMBER)
			return (car->registry[arena[pos] - 1]);
		return (0);
	}
	else
		return (0);
}
