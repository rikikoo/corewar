/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 09:53:54 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/02 18:26:58 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	execute_instruction(t_car *car, unsigned char *arena)
{
	if (car->current_opcode == 1)
//		return (stay_alive());
		return (1);
	else if (car->current_opcode == 4 || car->current_opcode == 5)
		return (arithmetic_inst(car->current_opcode, car, arena));
	else if (car->current_opcode >= 6 && car->current_opcode <= 8)
		return (bitwise_inst(car->current_opcode, car, arena));
	else
		return (1);
}

static void	exec_cars(t_game *game, unsigned char *arena)
{
	t_car	*car;

	car = game->cars;
	while (car)
	{
		car->current_opcode = arena[car->pos];
		car->cycles_to_exec -= (car->cycles_to_exec != 0);
		if (!car->cycles_to_exec)
			car->pos += execute_instruction(car, arena) % MEM_SIZE;
		car = car->next;
	}
}

int	start_cycles(t_flags flags, t_champ *champs, unsigned char *arena, \
t_game *game)
{
	while (1)
	{
		if (!game->cycles_to_die)
			champs++;
//			collect_the_dead(game, champs);
		exec_cars(game, arena);
		if (flags.dump && game->cycle >= flags.dump)
			return (0);
		if (game->winner)
			return (game->winner);
		game->cycle++;
		game->cycles_to_die--;
	}
}
