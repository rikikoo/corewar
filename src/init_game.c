/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:57:05 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/12 23:52:59 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	introduce_champs(t_champ *champs, int champ_count)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < champ_count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n", \
		champs[i].playernbr, champs[i].size, champs[i].name, champs[i].comment);
		i++;
	}
}

void	init_arena(t_champ *champs, int champ_count, unsigned char *arena)
{
	int				i;
	int				pos;

	i = 0;
	pos = 0;
	ft_bzero(arena, MEM_SIZE);
	while (i < champ_count)
	{
		ft_memcpy(&arena[pos], champs[i].exec, champs[i].size);
		pos += MEM_SIZE / champ_count;
		i++;
	}
	introduce_champs(champs, champ_count);
}

t_game	init_game(int champ, t_car *car)
{
	t_game	game;

	game.cycle = 0;
	game.lives = 0;
	game.cycles_to_die = CYCLE_TO_DIE;
	game.checks = 0;
	game.winner = 0;
	game.last_live_report = champ;
	game.cars = car;
	return (game);
}

/*
** initializes a carriage t_car for each champion and places them at the start
** of each champion's code. initializes t_game struct.
** finally calls start_cycles(), where the rest of the whole program's code is
** and which returns the winning champion's player number.
**
** @flags: struct containing the program flags and the total nbr of champions
** @champs: an array of champions
** @arena: the initialized arena
*/
int	start_game(t_flags flags, unsigned char *arena, t_champ *champs)
{
	t_car	*head;
	t_car	*car;
	t_game	game;
	int		i;

	i = flags.champ_count - 1;
	head = new_car(0, ((MEM_SIZE / flags.champ_count) * i), i);
	car = head;
	while (--i >= 0)
	{
		if (!car)
			return (-8);
		car->next = new_car(car->id, ((MEM_SIZE / flags.champ_count) * i), i);
		car = car->next;
	}
	game = init_game(flags.champ_count - 1, head);
	i = start_cycles(flags, arena, &game, champs);
	while (head != NULL)
	{
		car = head;
		head = head->next;
		free(car);
	}
	return (i);
}
