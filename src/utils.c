/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:17:42 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/12 23:01:16 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** initializes a new carriage, i.e. appends a new t_car element to the end of
** the carriage list, whose head pointer is stored in t_game
**
** @prev_id: id of previous carriage
** @pos: carriage position on the arena
** @playernbr: champion's playernbr; determined by parent carriage's registry[0]
*/
t_car	*new_car(int prev_id, int pos, int playernbr)
{
	t_car	*car;
	int		i;

	car = (t_car *)malloc(sizeof(t_car));
	if (!car)
		return (NULL);
	car->id = prev_id + 1;
	car->pos = pos;
	car->carry = 0;
	car->cycles_since_live = 0;
	car->dead = 0;
	car->cycles_to_exec = 1;
	car->next_instruction = 0;
	i = 0;
	car->registry[i] = playernbr * -1;
	while (++i < REG_NUMBER)
		car->registry[i] = 0;
	car->current_opcode = 0;
	car->next = NULL;
	return (car);
}

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
** returns either the first, second or third pair of bits of the 8-bit @byte.
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
** returns the size of an argument in bytes. T_DIR size depends on @inst_code.
*/
int	get_arg_size(int inst_code, int arg)
{
	if (arg == REG_CODE)
		return (T_REG);
	else if (arg == IND_CODE)
		return (IND_SIZE);
	else if (arg == DIR_CODE)
	{
		if ((inst >= 10 && inst <= 12) || inst >= 14)
			return (IND_SIZE);
		else
			return (DIR_SIZE);
	}
	else
		return (0);
}

/*
** TODO: ft_bytes_toint() might go over MEM_SIZE and thus SEGFAULT --> need to
** ensure correct reading of memory. program-specific n_bytes_reader function?
*/
int	get_arg_value(t_inst instruct, unsigned char *arena, t_car *car, int val)
{
	int	pos;
	int	ind_pos;

	if (val == 1)
		pos = (car->pos + 2) % MEM_SIZE;
	else
		pos = (car->pos + 2 + instruct.sizes[0]) % MEM_SIZE;
	if (instruct.types[val - 1] == T_REG)
		return (car->registry[arena[pos] - 1]);
	if (instruct.types[val - 1] == T_DIR)
		return ((int)ft_bytes_toint(arena[pos], instruct.sizes[val - 1]));
	if (instruct.types[val - 1] == T_IND)
	{
		ind_pos = (int)ft_bytes_toint(arena[pos], instruct.sizes[val - 1]) \
		% IDX_MOD;
		return ((int)ft_bytes_toint(arena[ind_pos % MEM_SIZE], DIR_SIZE));
	}
}
