/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 09:53:54 by rkyttala          #+#    #+#             */
/*   Updated: 2022/10/06 22:51:45 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	execute_instruction(
	t_game *game,
	t_car *car,
	unsigned char *arena,
	t_champ *champs
	)
{
	int	inst;

	inst = car->current_opcode;
	if (inst == 1)
		return (stay_alive(game, car, arena, champs));
	else if (inst == 2 || inst == 13)
		return (load_inst(inst, game, car, arena));
	else if (inst == 3)
		return (store_inst(game, car, arena));
	else if (inst == 4 || inst == 5)
		return (arithmetic_inst(inst, game, car, arena));
	else if (inst == 6 || inst == 7 || inst == 8)
		return (bitwise_inst(inst, game, car, arena));
	else if (inst == 9)
		return (jump_inst(game, car, arena));
	else if (inst == 10 || inst == 14)
		return (ind_load_inst(inst, game, car, arena));
	else if (inst == 11)
		return (ind_store_inst(game, car, arena));
	else if (inst == 12 || inst == 15)
		return (fork_inst(inst, game, car, arena));
	else if (inst == 16)
		return (print_aff(car, arena));
	else
		return (1);
}

/*
** Is there a cleaner way to achieve the following besides switch...case?
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
** for each carriage that is alive:
**	1. increase last_live
**	2. get new opcode if previous op execution was completed
**	3. decrease wait cycle timer (cycles_to_exec)
**	4. if wait cycle has ended, execute instruction and move carriage forward
*/
static int	exec_cars(t_game *game,
	unsigned char *arena,
	t_champ *champs,
	int ret)
{
	t_car	*car;

	car = game->cars;
	while (car)
	{
		car->last_live++;
		if (car->cycles_to_exec < 0)
		{
			car->current_opcode = arena[car->pos];
			car->cycles_to_exec = get_wait_cycles(car->current_opcode);
		}
		car->cycles_to_exec -= (car->cycles_to_exec > 0);
		if (car->cycles_to_exec == 0)
		{
			ret = execute_instruction(game, car, arena, champs);
			if (ret < 0)
				return (ret);
			car->pos = rel_pos(car->pos, ret) % MEM_SIZE;
			car->cycles_to_exec--;
		}
		car = car->next;
	}
	return (0);
}

int	start_cycles(unsigned char *arena, t_game *game, t_champ *champs)
{
	while (1)
	{
		game->cycle++;
		if ((game->flags.verbose & 1) == 1)
			ft_printf("Cycle: %d\n", game->cycle);
		if (exec_cars(game, arena, champs, 0) != 0)
			return (-8);
		if (game->cycle == game->next_check || game->cycle_to_die <= 0)
			game->winner = perform_check(game, NULL, NULL, 0);
		if (game->winner)
			return (game->winner);
		if (game->flags.dump && game->cycle == game->flags.dump)
			return (0);
	}
}
