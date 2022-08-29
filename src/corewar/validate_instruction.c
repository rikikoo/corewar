/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_instruction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/28 15:48:26 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** returns the number of arguments an instruction has, based on @inst_code
*/
int	get_arg_count(int inst_code)
{
	if (inst_code == 1 || inst_code == 9 || inst_code == 12 || inst_code == 15)
		return (1);
	else if (inst_code == 2 || inst_code == 3 || inst_code == 13)
		return (2);
	else
		return (3);
}

/*
** returns either the first, second or third pair of bits of the 8-bit @byte,
** starting from the left-most pair.
** @byte is the argument type code, while @arg is the argument's ordinal number.
** in other words, returns always either 0, 1, 2 or 3, which represent
** (respectively) NULL, T_REG, T_DIR or T_IND.
**
** example:
** @arg == 3, @byte == 0b01011000
**
** byte >> 2
**	=> 0b00010110	-- now the third bit-pair is shifted all the way to right
** byte & 3 == 0b00010110 & 0b00000011
**	=> 0b00000010 == 2 == T_DIR		-- ANDing the shifted byte with 3 (i.e. the
**									-- two right-most bits of a byte) yields the
**									-- value we were after
*/
int	get_arg_type(unsigned char byte, int arg)
{
	if (arg < 1 || arg > 3)
		return (0);
	if (arg == 1)
		return ((byte >> 6) & 3);
	else if (arg == 2)
		return ((byte >> 4) & 3);
	else
		return ((byte >> 2) & 3);
}

/*
** returns 1 (true) if all arguments that should be of type T_REG have a value
** between 1 and REG_NUMBER, 0 (false) otherwise
*/
static int	validate_regs(t_inst inst, unsigned char *arena, int pos)
{
	int	inst_code;
	int	reg;
	int	i;

	inst_code = inst.inst_code;
	if (inst_code == 1 || inst_code == 9 || inst_code == 12 || inst_code == 15)
		return (1);
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		reg = arena[pos % MEM_SIZE];
		if (inst.types[i] == T_REG && (reg < 1 || reg > REG_NUMBER))
			return (0);
		pos += inst.sizes[i];
		i++;
	}
	return (1);
}

/*
** depending on @inst_code, returns true of false (1 or 0; valid or invalid) if
** the argument types stored in @t are valid for that instruction.
**
** horrible to look at, I know... lines would be prettier if this wasn't a
** school project.
*/
static int	validate_args(int inst_code, int *t)
{
	if (inst_code == 1 || inst_code == 9 || inst_code == 12 || inst_code == 15)
		return (t[0] == DIR_CODE);
	else if (inst_code == 2)
		return ((t[0] == DIR_CODE || t[0] == IND_CODE) && t[1] == REG_CODE);
	else if (inst_code == 3)
		return (t[0] == REG_CODE && (t[1] == REG_CODE || t[1] == IND_CODE));
	else if (inst_code == 4 || inst_code == 5)
		return (t[0] == REG_CODE && t[1] == REG_CODE && t[2] == REG_CODE);
	else if (inst_code == 6 || inst_code == 7 || inst_code == 8)
		return ((t[0] == REG_CODE || t[0] == DIR_CODE || t[0] == IND_CODE) && \
		(t[1] == REG_CODE || t[1] == DIR_CODE || t[1] == IND_CODE) && \
		t[2] == REG_CODE);
	else if (inst_code == 10)
		return ((t[0] == REG_CODE || t[0] == DIR_CODE || t[0] == IND_CODE) && \
		(t[1] == REG_CODE || t[1] == DIR_CODE) && t[2] == REG_CODE);
	else if (inst_code == 11)
		return (t[0] == REG_CODE && (t[2] == REG_CODE || t[2] == DIR_CODE) && \
		(t[1] == REG_CODE || t[1] == DIR_CODE || t[1] == IND_CODE));
	else if (inst_code == 13)
		return ((t[0] == DIR_CODE || t[0] == IND_CODE) && t[1] == REG_CODE);
	else if (inst_code == 14)
		return ((t[0] == REG_CODE || t[0] == DIR_CODE || t[0] == IND_CODE) && \
		(t[1] == REG_CODE || t[1] == DIR_CODE) && t[2] == REG_CODE);
	else
		return (0);
}

/*
** Every instruction has a different amount of bytes that follow the instruction
** which determine how many bytes forward are regarded as the instruction's
** arguments.
*/
t_inst	validate_instruction(int inst_code, unsigned char *arena, int pos)
{
	int		n_args;
	int		arg;
	t_inst	inst;

	inst.inst_code = inst_code;
	n_args = get_arg_count(inst_code);
	pos = (pos + 1) % MEM_SIZE;
	ft_memset(inst.types, 0, MAX_ARGS_NUMBER * sizeof(int));
	arg = 0;
	while (++arg <= n_args)
		inst.types[arg - 1] = get_arg_type(arena[pos], arg);
	ft_memset(inst.sizes, 0, MAX_ARGS_NUMBER * sizeof(int));
	arg = -1;
	while (++arg < n_args)
		inst.sizes[arg] = get_arg_size(inst_code, inst.types[arg]);
	inst.is_valid = validate_args(inst.inst_code, inst.types);
	if (inst.is_valid)
		inst.is_valid = validate_regs(inst, arena, ++pos % MEM_SIZE);
	return (inst);
}
