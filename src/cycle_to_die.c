/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:54:12 by rkyttala          #+#    #+#             */
/*   Updated: 2022/05/10 19:14:36 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** marks carriages whose cycles_since_live is greater than cycles_to_die as dead
**
** TODO: cycles_to_die reset value has to be tracked and updated separately
** (unlike how it's done right now)
*/
void	collect_the_dead(t_game *game)
{
	t_car	*car;
	int		alive;

	car = game->cars;
	alive = 0;
	while (car)
	{
		car->dead = car->cycles_since_live >= game->cycles_to_die || car->dead;
		if (!car->dead)
			alive++;
		car = car->next;
	}
	if (!alive)
	{
		game->winner = game->last_live_report;
		return ;
	}
	if (game->checks >= NBR_LIVE)
		game->cycles_to_die = CYCLE_TO_DIE - CYCLE_DELTA;
	else
		game->cycles_to_die = CYCLE_TO_DIE - 1;
}
