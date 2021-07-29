/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:57:05 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/29 20:37:59 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_arena(t_champs *champs, int champ_count, unsigned char *arena)
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
}
