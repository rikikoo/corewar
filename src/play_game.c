/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 09:53:54 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/16 10:47:52 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** marks carriages whose cycles_since_live is greater than cycles_to_die as dead
*/
static void	collect_the_dead(t_game *game)
{
	t_car	*car;
	t_car	*prev;

	car = game->cars;
	prev = NULL;
	while (car)
	{
		if (!car->dead)
			car->dead = (car->cycles_since_live >= game->cycles_to_die);
		car = car->next;
	}
	if (game->checks >= NBR_LIVE)
		game->cycles_to_die = CYCLE_TO_DIE - CYCLE_DELTA;
	else
		game->cycles_to_die = CYCLE_TO_DIE - 1;

}

static int	execute_instruction(\
	t_game *game, \
	t_car *car, \
	unsigned char *arena, \
	t_champ *champs \
	)
{
	int	inst;

	inst = car->current_opcode;
	if (inst == 1)
		return (stay_alive(game, car, arena, champs));
	else if (inst == 2 || inst == 13)
		return (load_inst(inst, car, arena));
	else if (inst == 3)
		return (store_inst(car, arena));
	else if (inst == 4 || inst == 5)
		return (arithmetic_inst(inst, car, arena));
	else if (inst == 6 || inst == 7 || inst == 8)
		return (bitwise_inst(inst, car, arena));
	else if (inst == 9)
		return (jump_inst(car, arena));
	else if (inst == 10 || inst == 14)
		return (ind_load_inst(inst, car, arena));
	else if (inst == 11)
		return (ind_store_inst(car, arena));
	else if (inst == 12 || inst == 15)
		return (fork_inst(inst, car, arena, game));
	else if (inst == 16)
		return (print_aff(car, arena));
	else
		return (1);
}

/*
** Is there a cleaner way to achieve the following other than switch/case?
*/
static int	get_wait_cycles(int opcode)
{
	if (opcode == 1 || opcode == 4 || opcode == 5 || opcode == 13)
		return (10);
	else if (opcode == 2 || opcode == 3)
		return (5);
	else if (opcode == 6 || opcode == 7 || opcode == 8)
		return (6);
	else if (opcode == 9)
		return (20);
	else if (opcode == 10 || opcode == 11)
		return (25);
	else if (opcode == 12)
		return (800);
	else if (opcode == 14)
		return (50);
	else if (opcode == 15)
		return (1000);
	else if (opcode == 16)
		return (2);
	else
		return (1);
}

/*
** for each carriage:
**	1. increase cycles_since_live
**	2. if standing on a new opcode, update opcode and cycles_to_exec
**	3. decrease wait cycle timer (cycles_to_exec)
**	4. if wait cycle has ended, execute instruction and move carriage forward
*/
static void	exec_cars(t_game *game, unsigned char *arena, t_champ *champs)
{
	t_car	*car;

	car = game->cars;
	while (car)
	{
		if (!car->dead)
		{
			car->cycles_since_live++;
			if (car->current_opcode != arena[car->pos])
			{
				car->current_opcode = arena[car->pos];
				car->cycles_to_exec = get_wait_cycles(car->current_opcode);
			}
			car->cycles_to_exec -= (car->cycles_to_exec != 0);
			if (!car->cycles_to_exec)
				car->pos += execute_instruction(game, car, arena, champs) \
				% MEM_SIZE;
		}
		car = car->next;
	}
}

int	start_cycles(\
	t_flags flags, \
	unsigned char *arena, \
	t_game *game, \
	t_champ *champs \
	)
{
	while (1)
	{
		if (game->cycles_to_die <= 0)
			collect_the_dead(game);
		exec_cars(game, arena, champs);
		if (flags.dump && game->cycle >= flags.dump)
			return (0);
		if (game->winner)
			return (game->winner);
		game->cycle++;
		game->cycles_to_die--;
	}
}
