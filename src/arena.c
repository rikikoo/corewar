/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:57:05 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/22 17:03:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	init_arena(void)
{
	char	arena[MEM_SIZE];

	ft_bzero(&arena, MEM_SIZE);
	return (arena);
}
