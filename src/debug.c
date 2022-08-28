/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/12 00:42:16 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_cars(t_game *game)
{
	t_car	*car;
	int		i;

	car = game->cars;
	while (car)
	{
		ft_printf("%-23s: %d\n%-23s: (index %d)\n%-23s: %d\n", \
		"Car ID", car->id, "Position", car->pos, "Carry", car->carry);
		ft_printf("%-23s: %d\n%-23s: %d\n%-23s: %d\n%-23s\n", \
		"Cycles since live", car->last_live, "Current opcode", \
		car->current_opcode, "Cycles until execution", car->cycles_to_exec, \
		"Registry");
		i = -1;
		while (++i < REG_NUMBER)
			ft_printf("\t%s%-2d : %d\n", "r", i + 1, car->registry[i]);
		car = car->next;
		ft_putchar('\n');
	}
}
