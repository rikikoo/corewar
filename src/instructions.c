/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:35:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/02 18:31:29 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** perform addition with the values of the first two argument registers if
** @inst == 4 and subtraction if @inst == 5. store the result into third reg.
** if the result of either operation is 0, change carry to true.
*/
int	arithmetic_inst(int inst, t_car *car, unsigned char *arena)
{
	int	first_arg_pos;

	first_arg_pos = car->pos + 2;
	if (inst == 4)
		car->registry[arena[first_arg_pos + (T_REG * 2)]] = \
		car->registry[arena[first_arg_pos]] + \
		car->registry[arena[first_arg_pos + T_REG]];
	else if (inst == 5)
		car->registry[arena[first_arg_pos + (T_REG * 2)]] = \
		car->registry[arena[first_arg_pos]] - \
		car->registry[arena[first_arg_pos + T_REG]];
	if (car->registry[arena[first_arg_pos + (T_REG * 2)]] == 0)
		car->carry = 1;
	else
		car->carry = 0;
	return (0);
}

/*
** perform bitwise AND (&) with the values of the first two arguments
** if @inst == 6, bitwise OR (|) if @inst == 7, bitwise XOR (^) if @inst == 8.
** store the result into the third register.
** if the result of any of the operations is 0, change carry to true.
*/
int	bitwise_inst(int inst, t_car *car, unsigned char *arena)
{
	int	first_arg_pos;

	first_arg_pos = car->pos;
	if (inst == 6)
		car->registry[arena[first_arg_pos + (T_REG * 2)]] = \
		car->registry[arena[first_arg_pos]] & \
		car->registry[arena[first_arg_pos + T_REG]];
	else if (inst == 7)
		car->registry[arena[first_arg_pos + (T_REG * 2)]] = \
		car->registry[arena[first_arg_pos]] | \
		car->registry[arena[first_arg_pos + T_REG]];
	else if (inst == 8)
		car->registry[arena[first_arg_pos + (T_REG * 2)]] = \
		car->registry[arena[first_arg_pos]] ^ \
		car->registry[arena[first_arg_pos + T_REG]];
	if (car->registry[arena[first_arg_pos + (T_REG * 2)]] == 0)
		car->carry = 1;
	else
		car->carry = 0;
	return (0);
}
