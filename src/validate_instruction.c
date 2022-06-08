/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_instruction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2022/06/03 23:35:52 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** returns 1 (true) if all arguments that should be of type T_REG have a value
** between 1 and REG_NUMBER, 0 (false) otherwise
*/
static int	validate_regs(t_inst instruct, unsigned char *arena, int pos)
{
	int	inst_code;
	int	reg;
	int	i;

	inst_code = instruct.inst_code;
	if (inst_code == 1 || inst_code == 9 || inst_code == 12 || inst_code == 15)
		return (1);
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		reg = arena[pos % MEM_SIZE];
		if (instruct.types[i] == T_REG && (reg < 1 || reg > REG_NUMBER))
			return (0);
		pos += instruct.sizes[i];
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
		return (t[0] == T_REG && (t[2] == REG_CODE || t[2] == DIR_CODE) && \
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
	t_inst	instruct;

	instruct.inst_code = inst_code;
	n_args = get_arg_count(inst_code);
	pos = (pos + 1) % MEM_SIZE;
	ft_memset(instruct.types, 0, MAX_ARGS_NUMBER * sizeof(int));
	arg = 0;
	while (++arg <= n_args)
		instruct.types[arg - 1] = get_arg_type(arena[pos], arg);
	ft_memset(instruct.sizes, 0, MAX_ARGS_NUMBER * sizeof(int));
	arg = -1;
	while (++arg < n_args)
		instruct.sizes[arg] = get_arg_size(inst_code, instruct.types[arg]);
	instruct.is_valid = validate_args(instruct.inst_code, instruct.types);
	if (instruct.is_valid)
		instruct.is_valid = validate_regs(instruct, arena, ++pos % MEM_SIZE);
	return (instruct);
}
