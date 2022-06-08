/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:57:32 by rkyttala          #+#    #+#             */
/*   Updated: 2022/06/07 23:24:53 by rkyttala         ###   ########.fr       */
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
	int	new_pos;

	if (car->carry)
	{
		if (game->flags.verbose)
			ft_printf("Process %d (of player number %d): %s %d\n", \
			car->id, car->registry[0] * -1, "zjmp", \
			n_bytes_to_int(arena, (car->pos + 1) % MEM_SIZE, IND_SIZE));
		new_pos = n_bytes_to_int(arena, (car->pos + 1) % MEM_SIZE, IND_SIZE);
		return (new_pos % IDX_MOD);
	}
	else
		return (0);
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
	value1 = get_arg_value(instruct, arena, car, 1);
	value2 = get_arg_value(instruct, arena, car, 2);
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
	int				dst_pos;
	int				reg;
	int				value1;
	int				value2;
	t_inst			instruct;

	instruct = validate_instruction(11, arena, car->pos);
	if (game->flags.verbose)
		print_verbose(car, instruct, arena, 1);
	if (!instruct.is_valid)
		return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
	reg = arena[(car->pos + 2) % MEM_SIZE];
	value1 = get_arg_value(instruct, arena, car, 2);
	value2 = get_arg_value(instruct, arena, car, 3);
	dst_pos = (value1 + value2) % IDX_MOD;
	swap_endianness((unsigned char *)&car->registry[reg - 1], REG_SIZE);
	ft_memcpy(&arena[(car->pos + dst_pos) % MEM_SIZE], \
		(unsigned char *)&car->registry[reg - 1], REG_SIZE);

	ft_printf("store %#x to %d\n", \
	car->registry[arena[(car->pos + 2) % MEM_SIZE]], \
		(car->pos + dst_pos) % MEM_SIZE);

	return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
}

int	fork_inst(int inst_code, t_game *game, t_car *car, unsigned char *arena)
{
	int		new_pos;
	t_car	*car_new;
	t_car	*first_car;
	int		reg_i;

	new_pos = n_bytes_to_int(arena, (car->pos + 1) % MEM_SIZE, IND_SIZE);
	if (inst_code == 12)
		new_pos = new_pos % IDX_MOD;
	if (game->flags.verbose)
		ft_printf("Process %d (of player number %d): %s %d\n", \
		car->id, car->registry[0] * -1, "lfork"[(inst_code == 12)], \
		n_bytes_to_int(arena, (car->pos + 1) % MEM_SIZE, IND_SIZE));
	first_car = game->cars;
	car_new = new_car(first_car->id, new_pos % MEM_SIZE, car->registry[0] * -1);
	if (!car_new)
		return (-1);
	car_new->next = first_car;
	game->cars = car_new;
	reg_i = 1;
	while (reg_i < REG_NUMBER)
	{
		car_new->registry[reg_i] = car->registry[reg_i];
		reg_i++;
	}
	car_new->carry = car->carry;
	car_new->cycles_since_live = car->cycles_since_live;
	return (IND_SIZE + 1);
}
