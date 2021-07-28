/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:57:05 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/28 22:23:26 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	init_arena(void)
{
	unsigned char	arena[MEM_SIZE];

	ft_bzero(arena, MEM_SIZE);
	return (arena);
}
