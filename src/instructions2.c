/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:57:32 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/18 23:12:52 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** moves @car to a new position on @arena if car->carry == true
**
** TODO: should the instruction be skipped if carry == 0, or not?
*/
int	jump_inst(t_game *game, t_car *car, unsigned char *arena)
{
	short	new_pos;

	new_pos = ((arena[(car->pos + 1) % MEM_SIZE] << 8) \
	+ arena[(car->pos + 2) % MEM_SIZE]) % IDX_MOD;
	if (game->flags.verbose)
	{
		ft_printf("Process %d: %s %hd ", car->id, "zjmp", new_pos);
		if (car->carry)
			ft_printf("OK\n");
		else
			ft_printf("FAILED\n");
	}
	if (car->carry)
		return (new_pos);
	else
		return (1 + IND_SIZE);
}

int	ind_load_inst(int inst_code, t_game *game, t_car *car, unsigned char *arena)
{
	int		pos;
	int		value1;
	int		value2;
	int		reg;
	t_inst	instruct;

	instruct = validate_instruction(inst_code, arena, car->pos);
	if (game->flags.verbose)
		print_verbose(car, instruct, arena, 1);
	if (!instruct.is_valid)
		return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
	pos = car->pos + 2;
	value1 = get_arg_val(instruct, arena, car, 1);
	value2 = get_arg_val(instruct, arena, car, 2);
	reg = arena[(pos + instruct.sizes[0]) % MEM_SIZE] - 1;
	if (inst_code == 10)
		car->registry[reg] = (value1 + value2) % IDX_MOD;
	else
		car->registry[reg] = value1 + value2;
	if (inst_code == 14)
		car->carry = (car->registry[reg] == 0);
	return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
}

int	ind_store_inst(t_game *game, t_car *car, unsigned char *arena)
{
	int		dst_pos;
	int		reg_val;
	int		value1;
	int		value2;
	t_inst	instruct;

	instruct = validate_instruction(11, arena, car->pos);
	if (game->flags.verbose)
		print_verbose(car, instruct, arena, 1);
	if (!instruct.is_valid)
		return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
	reg_val = get_arg_val(instruct, arena, car, 1);
	value1 = get_arg_val(instruct, arena, car, 2);
	value2 = get_arg_val(instruct, arena, car, 3);
	dst_pos = (value1 + value2) % IDX_MOD;
	swap_endianness((unsigned char *)&reg_val, REG_SIZE);
	ft_memcpy(&arena[(car->pos + dst_pos) % MEM_SIZE], \
	(unsigned char *)&reg_val, REG_SIZE);
	return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
}

static int	add_forked_car(t_game *game, t_car *parent, int fork_pos)
{
	t_car	*car_new;
	t_car	*old_first;
	int		reg_i;

	old_first = game->cars;
	car_new = new_car(game->latest_car_id, fork_pos, parent->registry[0] * -1);
	if (!car_new)
		return (-1);
	car_new->next = old_first;
	reg_i = 1;
	while (reg_i < REG_NUMBER)
	{
		car_new->registry[reg_i] = parent->registry[reg_i];
		reg_i++;
	}
	car_new->carry = parent->carry;
	car_new->cycles_since_live = parent->cycles_since_live;
	game->cars = car_new;
	game->latest_car_id = car_new->id;
	return (0);
}

int	fork_inst(int inst_code, t_game *game, t_car *car, unsigned char *arena)
{
	int		fork_pos;
	char	*inst_name;

	inst_name = "lfork";
	inst_name = inst_name + (inst_code == 12);
	fork_pos = (arena[(car->pos + 1) % MEM_SIZE] << 8) \
	+ arena[(car->pos + 2) % MEM_SIZE];
	if (inst_code == 12)
		fork_pos = fork_pos % IDX_MOD;
	if (game->flags.verbose)
		ft_printf("Process %d: %s %d\n", car->id, inst_name, fork_pos);
	if (add_forked_car(game, car, (car->pos + fork_pos) % MEM_SIZE) < 0)
		return (-1);
	return (IND_SIZE + 1);
}
