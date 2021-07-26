/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:05:26 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/26 10:06:34 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** treats the byte pointed to by @bytes as the most significant byte of a
** series of four bytes forward.
*/
unsigned int	four_bytes_toint(const unsigned char *bytes)
{
	unsigned int	nb;

	nb = (unsigned int)bytes[0] << 24;
	nb += (unsigned int)bytes[1] << 16;
	nb += (unsigned int)bytes[2] << 8;
	nb += (unsigned int)bytes[3];
	return (nb);
}
