/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:54:12 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/23 20:19:03 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
** marks carriages whose cycles_since_live is greater than cycle_to_die as dead
** and updates cycle_to_die if necessary
*/
int	collect_the_dead(t_game *game)
{
	t_car		*car;
	int			alive;

	car = game->cars;
	alive = 0;
	game->checks++;
	// debug
	// ft_printf("Cycle: %d\tTo die: %d\tDelta: %d\n", \
	// game->cycle, game->cycle_to_die, die_cycle_delta);
	// debug end
	while (car)
	{
		//debug
		// ft_printf("Car %d cycles since live: %d\n", \
		// car->registry[0] * -1, car->cycles_since_live);
		// debug end

		if (car->cycles_since_live >= game->cycle_to_die)
			car = remove_dead_car(game, car->id);
		else
			alive++;
		if (car)
			car = car->next;
	}
	// ft_printf("exit car loop with %d alive\n", alive);
	if (!alive)
		return (game->last_live_report);
	if (game->live_count >= NBR_LIVE || game->checks >= MAX_CHECKS)
	{
		game->cycle_to_die -= CYCLE_DELTA;
		game->checks = 0;
	}
	game->live_count = 0;
	return (0);
}
