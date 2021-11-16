/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:57:32 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/16 11:35:11 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** moves @car to a new position on @arena if car->carry == true
**
** TODO: should the instruction be skipped if carry == 0, or not?
*/
int	jump_inst(t_car *car, unsigned char *arena)
{
	int	new_pos;

	if (car->carry)
	{
		new_pos = n_bytes_to_int(&arena[(car->pos + 1) % MEM_SIZE], IND_SIZE);
		return (new_pos % IDX_MOD);
	}
	else
		return (0);
}

int	ind_load_inst(int inst_code, t_car *car, unsigned char *arena)
{
	int		pos;
	int		value1;
	int		value2;
	int		reg;
	t_inst	instruct;

	instruct = validate_instruction(inst_code, arena, car->pos);
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

int	ind_store_inst(t_car *car, unsigned char *arena)
{
	int		pos;
	int		reg_value;
	int		value1;
	int		value2;
	t_inst	instruct;

	instruct = validate_instruction(11, arena, car->pos);
	if (!instruct.is_valid)
		return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
	reg_value = get_arg_value(instruct, arena, car, 1);
	value1 = get_arg_value(instruct, arena, car, 2);
	value2 = get_arg_value(instruct, arena, car, 3);
	pos = (car->pos + value1 + value2) % IDX_MOD;
	arena[pos % MEM_SIZE] = reg_value;
	return (instruct.sizes[0] + instruct.sizes[1] + instruct.sizes[2] + 2);
}

int	fork_inst(int inst_code, t_car *car, unsigned char *arena, t_game *game)
{
	int		new_pos;
	t_car	*car_new;
	t_car	*last_car;
	int		reg_i;

	new_pos = n_bytes_to_int(&arena[(car->pos + 1) % MEM_SIZE], IND_SIZE);
	if (inst_code == 12)
		new_pos = new_pos % IDX_MOD;
	last_car = game->cars;
	while (last_car->next != NULL)
		last_car = last_car->next;
	car_new = new_car(last_car->id, new_pos % MEM_SIZE, car->registry[0] * -1);
	last_car->next = car_new;
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
