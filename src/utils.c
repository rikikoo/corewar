/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:17:42 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/28 12:09:18 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** returns @n contiguous bytes converted to an int, if 0 < n <= sizeof(int)
*/
int	bytes_to_int(const unsigned char *arena, int pos, int n)
{
	int	nbr;
	int	bits;

	if (!arena || n <= 0 || n > (int) sizeof(int))
		return (0);
	nbr = 0;
	bits = 0;
	while (--n >= 0)
	{
		nbr += arena[(pos + n) % MEM_SIZE] << bits;
		bits += 8;
	}
	return (nbr);
}

/*
** reverses order of bytes in the array @bytes of size @len
*/
void	swap_endianness(unsigned char *bytes, int len)
{
	unsigned char	tmp;
	int				i;
	int				halfway;

	i = 0;
	halfway = len / 2;
	while (len > halfway)
	{
		len--;
		tmp = bytes[i];
		bytes[i] = bytes[len];
		bytes[len] = tmp;
		i++;
	}
}

/*
** returns a new position of a carriage, where @relative_pos is the amount of
** steps forward or backward from @car_pos. Makes sure the new position is
** inside the arena.
*/
int	rel_pos(int car_pos, int relative_pos)
{
	int	new_pos;

	new_pos = car_pos + relative_pos;
	new_pos %= MEM_SIZE;
	if (new_pos < 0)
		new_pos = MEM_SIZE + new_pos;
	return (new_pos);
}

/*
** copies @len bytes from @src into @arena, while truncating each step forward
** with mod MEM_SIZE to make sure the @arena buffer isn't overflown
*/
void	write_to_arena(unsigned char *arena,
		unsigned char *src,
		int start,
		int len
		)
{
	int	i;

	i = 0;
	while (i < len)
	{
		arena[(start + i) % MEM_SIZE] = src[i];
		i++;
	}
}
