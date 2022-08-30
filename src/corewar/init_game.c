/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:57:05 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/30 21:35:18 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** allocates memory and initializes a new carriage, i.e. appends a new t_car
** element to the end of the carriage list, whose head pointer is in t_game
**
** @last_id: id of previous carriage
** @pos: carriage position on the arena
** @playernbr: champion's playernbr; determined by parent carriage's registry[0]
*/
t_car	*new_car(int last_id, int pos, int playernbr)
{
	t_car	*car;
	int		i;

	car = (t_car *)malloc(sizeof(t_car));
	if (!car)
		return (NULL);
	car->id = last_id + 1;
	car->pos = pos % MEM_SIZE;
	car->carry = 0;
	car->last_live = 1;
	car->cycles_to_exec = -1;
	i = 0;
	car->registry[i] = playernbr * -1;
	while (++i < REG_NUMBER)
		car->registry[i] = 0;
	car->current_opcode = 0;
	car->next = NULL;
	return (car);
}

static t_game	init_game(t_flags flags, t_car *car, int latest_id)
{
	t_game	game;

	game.cycle = 0;
	game.lives = 0;
	game.cycle_to_die = CYCLE_TO_DIE;
	game.next_check = CYCLE_TO_DIE;
	game.checks = 0;
	game.winner = 0;
	game.live_count = 0;
	game.latest_car_id = latest_id;
	game.last_live_report = flags.champ_count;
	game.cars = car;
	game.flags = flags;
	return (game);
}

static t_car	*init_cars(t_flags flags, int player)
{
	t_car	*head;
	t_car	*last;

	last = new_car(0, ((MEM_SIZE / flags.champ_count) * (player - 1)), player);
	head = last;
	if (!head)
		return (NULL);
	while (++player <= flags.champ_count)
	{
		head = new_car(last->id, \
		((MEM_SIZE / flags.champ_count) * (player - 1)), player);
		if (!head)
		{
			while (last)
			{
				head = last;
				last = last->next;
				free(head);
			}
			return (NULL);
		}
		head->next = last;
		last = head;
	}
	return (head);
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
	t_game	game;
	int		player;

	player = 1;
	head = init_cars(flags, player);
	if (!head)
		return (-8);
	game = init_game(flags, head, head->id);
	player = start_cycles(arena, &game, champs);
	while (game.cars != NULL)
	{
		head = game.cars;
		game.cars = game.cars->next;
		free(head);
	}
	return (player);
}
