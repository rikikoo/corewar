/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:35:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/10/30 18:30:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	stay_alive(t_game *game, t_car *car)
{
	car->cycles_since_live = 0;
	game->last_live_report = car->registry[0] * -1;
	return (1);
}

/*
** performs a load, store, load index or store index operation
** (instruction 2, 3, 10 or 11 respectively).
*/
int	loadstore_inst(int inst, t_car *car, unsigned char *arena)
{
	if (inst == 2)
	{
		return (car->pos + arena[car->pos]);	// placeholder
	}
	else if (inst == 3)
	{
		return (car->pos + 1);	// placeholder
	}
	else if (inst == 10)
	{
		return (car->pos + 1);	// placeholder
	}
	else if (inst == 11)
	{
		return (car->pos + 1);	// placeholder
	}
	return (1);
}

/*
** performs addition with the values in the first two registers if @inst == 4
** and subtraction if @inst == 5. stores the result into third reg.
** if the result of the operation is 0, changes carry to true.
*/
int	arithmetic_inst(int inst, t_car *car, unsigned char *arena)
{
	int	value_reg1;
	int value_reg2;
	int	reg3;

	value_reg1 = car->registry[arena[(car->pos + 2) % MEM_SIZE]];
	value_reg2 = car->registry[arena[(car->pos + 2 + T_REG) % MEM_SIZE]];
	reg3 = arena[(car->pos + 2 + (T_REG * 2)) % MEM_SIZE];
	if (inst == 4)
		car->registry[reg3] = value_reg1 + value_reg2;
	else if (inst == 5)
		car->registry[reg3] = value_reg1 - value_reg2;
	else
		return (1);
	car->carry = (car->registry[reg3] == 0);
	return (0);		// placeholder return value, should return car moves
}

/*
** performs a bitwise operation with the values in the first two registers and
** stores the result into the third register.
** if the result of the operation is 0, changes carry to true.
*/
int	bitwise_inst(int inst, t_car *car, unsigned char *arena)
{
	int	value_reg1;
	int value_reg2;
	int	reg3;

	value_reg1 = car->registry[arena[car->pos]];
	value_reg2 = car->registry[arena[(car->pos + T_REG) % MEM_SIZE]];
	reg3 = arena[(car->pos + (T_REG * 2)) % MEM_SIZE];
	if (inst == 6)
		car->registry[reg3] = value_reg1 & value_reg2;
	else if (inst == 7)
		car->registry[reg3] = value_reg1 | value_reg2;
	else if (inst == 8)
		car->registry[reg3] = value_reg1 ^ value_reg2;
	else
		return (1);
	car->carry = (car->registry[reg3] == 0);
	return (0);		// placeholder return value, should return car moves
}
