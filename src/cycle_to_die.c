/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:54:12 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/28 11:05:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	reduce_cycle_to_die(t_game *game)
{
	if (game->live_count >= NBR_LIVE || game->checks >= MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->checks = 0;
		if ((game->flags.verbose & 1) == 1)
			ft_printf("\033[91mCycle to die is now %d\033[0m\n", \
				game->cycle_to_die);
	}
	game->next_check += game->cycle_to_die;
	game->live_count = 0;
}

/*
** removes a car from the list of cars
*/
static t_car	*remove_dead_car(t_game *game, int dead_car)
{
	t_car	*prev;
	t_car	*car;
	t_car	*next;

	prev = NULL;
	car = game->cars;
	while (car)
	{
		next = car->next;
		if (car->id == dead_car)
		{
			if (car->id == game->cars->id)
				game->cars = next;
			else
			{
				prev->next = next;
				free(car);
				car = NULL;
			}
			break ;
		}
		prev = car;
		car = car->next;
	}
	return (next);
}

/*
** removes carriages whose cycles_since_live is greater than cycle_to_die
** and updates cycle_to_die if necessary. returns the winning player's number if
** all carriages are dead, which ends the game.
*/
int	perform_check(t_game *game)
{
	t_car		*car;
	int			alive;

	car = game->cars;
	alive = 0;
	game->checks++;
	while (car)
	{
		if (car->cycles_since_live >= game->cycle_to_die)
		{
			ft_printf("Process %d died\n", car->id);
			car = remove_dead_car(game, car->id);
		}
		else
			alive++;
		if (car)
			car = car->next;
	}
	if (!alive)
		return (game->last_live_report);
	reduce_cycle_to_die(game);
	return (0);
}
