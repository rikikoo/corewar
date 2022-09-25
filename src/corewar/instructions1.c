/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:35:39 by rkyttala          #+#    #+#             */
/*   Updated: 2022/09/25 13:00:35 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	stay_alive(t_game *game, t_car *car, unsigned char *arena, t_champ *champs)
{
	int	player;

	player = bytes_to_int(arena, (car->pos + 1) % MEM_SIZE, DIR_SIZE);
	if ((game->flags.verbose & 2) == 2)
		ft_printf("Process %d : live %d\n", car->id, player);
	if ((player < 0) && (player * -1 <= game->flags.champ_count))
	{
		player = ft_abs(player);
		if ((game->flags.verbose & 8) == 8)
			print_live(champs[player - 1]);
		game->last_live_report = player;
	}
	car->last_live = 0;
	game->live_count++;
	return (DIR_SIZE + 1);
}

/*
** performs a load or long load operation (@inst_code == 2 or 13, respectively).
** if the loaded value is 0, changes carry to true.
*/
int	load_inst(int inst_code, t_game *game, t_car *car, unsigned char *arena)
{
	short	ind_pos;
	int		value;
	int		reg;
	t_inst	inst;

	inst = validate_instruction(inst_code, arena, car->pos);
	if (((game->flags.verbose & 6) == 2 && inst.is_valid) || \
	(!inst.is_valid && (game->flags.verbose & 4) == 4))
		print_instruction(car, inst, arena);
	if (!inst.is_valid)
		return (inst.sizes[0] + inst.sizes[1] + 2);
	if (inst.types[0] == IND_CODE)
	{
		ind_pos = get_ind_val(inst, arena, car, 1);
		if (inst.inst_code == 2)
			ind_pos = ind_pos % IDX_MOD;
		value = bytes_to_int(arena, rel_pos(car->pos, ind_pos), DIR_SIZE);
	}
	else
		value = get_arg_val(inst, arena, car, 1);
	reg = arena[(car->pos + 2 + inst.sizes[0]) % MEM_SIZE] - 1;
	car->registry[reg] = value;
	car->carry = (value == 0);
	return (inst.sizes[0] + inst.sizes[1] + 2);
}

/*
** performs a store operation (@inst_code == 3).
*/
int	store_inst(t_game *game, t_car *car, unsigned char *arena)
{
	int		pos;
	short	ind_value;
	int		reg_value;
	t_inst	inst;

	inst = validate_instruction(3, arena, car->pos);
	if (((game->flags.verbose & 6) == 2 && inst.is_valid) || \
	(!inst.is_valid && (game->flags.verbose & 4) == 4))
		print_instruction(car, inst, arena);
	if (!inst.is_valid)
		return (inst.sizes[0] + inst.sizes[1] + 2);
	pos = car->pos + inst.sizes[0] + 2;
	reg_value = get_arg_val(inst, arena, car, 1);
	if (inst.types[1] == REG_CODE)
		car->registry[arena[pos % MEM_SIZE] - 1] = reg_value;
	else
	{
		ind_value = get_ind_val(inst, arena, car, 2) % IDX_MOD;
		swap_endianness((unsigned char *)&reg_value, REG_SIZE);
		write_to_arena(arena, (unsigned char *)&reg_value, \
			rel_pos(car->pos, ind_value), REG_SIZE);
	}
	return (inst.sizes[0] + inst.sizes[1] + 2);
}

/*
** performs addition or subtraction (@inst_code == 4 or 5, respectively) with
** the values in the first two registers and stores the result into third reg.
** if the result of the operation is 0, changes carry to true.
*/
int	arithmetic_inst(int inst_code,
	t_game *game,
	t_car *car,
	unsigned char *arena
	)
{
	int		pos;
	int		value1;
	int		value2;
	int		reg;
	t_inst	inst;

	inst = validate_instruction(inst_code, arena, car->pos);
	if (((game->flags.verbose & 6) == 2 && inst.is_valid) || \
	(!inst.is_valid && (game->flags.verbose & 4) == 4))
		print_instruction(car, inst, arena);
	if (!inst.is_valid)
		return (inst.sizes[0] + inst.sizes[1] + inst.sizes[2] + 2);
	pos = car->pos + 2;
	value1 = get_arg_val(inst, arena, car, 1);
	value2 = get_arg_val(inst, arena, car, 2);
	reg = arena[(pos + inst.sizes[0] + inst.sizes[1]) % MEM_SIZE] - 1;
	if (inst_code == 4)
		car->registry[reg] = value1 + value2;
	else if (inst_code == 5)
		car->registry[reg] = value1 - value2;
	else
		return (1);
	car->carry = (car->registry[reg] == 0);
	return (inst.sizes[0] + inst.sizes[1] + inst.sizes[2] + 2);
}

/*
** performs a bitwise operation with the values of the first two arguments and
** stores the result into the register pointed to by the third argument.
** if the result of the operation is 0, changes carry to true.
*/
int	bitwise_inst(int inst_code, t_game *game, t_car *car, unsigned char *arena)
{
	int		reg_pos;
	int		values[2];
	int		reg;
	t_inst	inst;

	inst = validate_instruction(inst_code, arena, car->pos);
	if (((game->flags.verbose & 6) == 2 && inst.is_valid) || \
	(!inst.is_valid && (game->flags.verbose & 4) == 4))
		print_instruction(car, inst, arena);
	if (!inst.is_valid)
		return (inst.sizes[0] + inst.sizes[1] + inst.sizes[2] + 2);
	get_inst_operands(inst, arena, car, values);
	reg_pos = car->pos + 2 + inst.sizes[0] + inst.sizes[1];
	reg = arena[reg_pos % MEM_SIZE] - 1;
	if (inst_code == 6)
		car->registry[reg] = values[0] & values[1];
	else if (inst_code == 7)
		car->registry[reg] = values[0] | values[1];
	else if (inst_code == 8)
		car->registry[reg] = values[0] ^ values[1];
	car->carry = (car->registry[reg] == 0);
	return (inst.sizes[0] + inst.sizes[1] + inst.sizes[2] + 2);
}
