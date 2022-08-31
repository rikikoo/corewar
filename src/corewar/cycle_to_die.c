/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:54:12 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/31 23:07:56 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	reduce_cycle_to_die(t_game *game)
{
	game->checks++;
	if (game->live_count >= NBR_LIVE || game->checks >= MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->checks = 0;
		if ((game->flags.verbose & 1) == 1)
			ft_printf("Cycle to die is now %d\n", game->cycle_to_die);
	}
	game->next_check += game->cycle_to_die;
	game->live_count = 0;
}

/*
** removes a car from the list of cars
*/
static t_car	*remove_dead_car(t_game *game, t_car *car, t_car *prev)
{
	t_car	*next;

	next = car->next;
	if (car->id == game->cars->id || prev == NULL)
		game->cars = next;
	else
		prev->next = next;
	free(car);
	return (prev);
}

/*
** removes carriages whose last_live is greater than cycle_to_die and updates
** cycle_to_die if necessary. returns the winning player's number if all
** carriages are dead, which ends the game.
*/
int	perform_check(t_game *game, t_car *prev, t_car *next, int alive)
{
	t_car	*car;

	car = game->cars;
	while (car)
	{
		next = car->next;
		if (car->last_live >= game->cycle_to_die || game->cycle_to_die <= 0)
		{
			if ((game->flags.verbose & 8) == 8)
				ft_printf("Process %d died (last live: %d >= CTD: %d)\n", \
				car->id, car->last_live, game->cycle_to_die);
			prev = remove_dead_car(game, car, prev);
		}
		else
		{
			alive++;
			prev = car;
		}
		car = next;
	}
	reduce_cycle_to_die(game);
	if (!alive)
		return (game->last_live_report);
	return (0);
}
