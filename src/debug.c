/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/10 01:37:29 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_arg_types(unsigned char *arena, t_car *car, t_inst instruct)
{
	int	i;

	i = 0;
	ft_printf("Argument coding byte: %#2x", arena[(car->pos + 1) % MEM_SIZE]);
	ft_printf(" ( ");
	while (instruct.types[i] && i < 4)
	{
		ft_printf("%d ", instruct.types[i]);
		i++;
	}
	ft_printf(")");
	ft_putchar('\n');
}

void	print_cars(t_game *game, t_champ *champs)
{
	t_car	*car;
	int		i;

	car = game->cars;
	while (car)
	{
		ft_printf("%-23s: %d\n%-23s: %s\n%-23s: (index %d)\n%-23s: %d\n", \
		"Car ID", car->id, "Owner", champs[(car->registry[0] * -1) - 1].name, \
		"Position", car->pos, "Carry", car->carry);
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
