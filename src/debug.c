/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/18 15:16:45 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_cars(t_game *game, t_champ *champs, unsigned char *arena)
{
	t_car	*car;
	int		i;

	car = game->cars;
	while (car)
	{
		ft_printf("%-23s: %d\n%-23s: %s\n%-23s: %p (index %d)\n%-23s: %d\n", \
		"Car ID", car->id, "Owner", champs[(car->registry[0] * -1) - 1].name, \
		"Position", &arena[car->pos], car->pos, "Carry", car->carry);
		if (car->dead)
			ft_printf("%-23s: %s\n", "Car dead", "True");
		else
			ft_printf("%-23s: %s\n", "Car dead", "False");
		ft_printf("%-23s: %d\n%-23s: %d\n%-23s: %d\n%-23s\n", \
		"Cycles since live", car->cycles_since_live, "Current opcode", \
		car->current_opcode, "Cycles until execution", car->cycles_to_exec, \
		"Registry");
		i = -1;
		while (++i < REG_NUMBER)
			ft_printf("\t%s%-2d : %d\n", "r", i + 1, car->registry[i]);
		car = car->next;
		ft_putchar('\n');
	}
}
