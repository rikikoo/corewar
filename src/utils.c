/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:17:42 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/11 22:00:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_n_bytes(unsigned char *arena, int pos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_printf("%02x ", arena[pos % MEM_SIZE]);
		pos++;
		i++;
	}
	ft_putchar('\n');
}

/*
** returns @n contiguous bytes converted to an int, if 0 < n <= sizeof(int)
*/
int	n_bytes_to_int(const unsigned char *arena, int pos, int n)
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
    int             halfway;

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
** returns the number of arguments an instruction has, based on @inst_code
*/
int	get_arg_count(int inst_code)
{
	if (inst_code == 1 || inst_code == 9 || inst_code == 12 || inst_code == 15)
		return (1);
	else if (inst_code == 2 || inst_code == 3 || inst_code == 13)
		return (2);
	else
		return (3);
}

/*
** returns either the first, second or third pair of bits of the 8-bit @byte.
** @byte is the argument type code, while @arg is the argument's ordinal number.
** in other words, returns always either 0, 1, 2 or 3, which represent
** (respectively) NULL, T_REG, T_DIR or T_IND.
**
** example:
** @arg == 3, @byte == 0b01011000
**
** byte >> 2
**	=> 0b00010110	-- now the third bit-pair is shifted all the way to right
** byte & 3 == 0b00010110 & 0b00000011
**	=> 0b00000010 == 2 == T_DIR		-- ANDing the shifted byte with 3 (i.e. the
**									-- two right-most bits of a byte) yields the
**									-- value we were after
*/
int	get_arg_type(unsigned char byte, int arg)
{
	if (arg < 1 || arg > 3)
		return (0);
	if (arg == 1)
		return ((byte >> 6) & 3);
	else if (arg == 2)
		return ((byte >> 4) & 3);
	else
		return ((byte >> 2) & 3);
}

/*
** returns the size of an argument in bytes. T_DIR size depends on @inst_code.
*/
int	get_arg_size(int inst_code, int arg)
{
	if (arg == REG_CODE)
		return (REG_CODE);
	else if (arg == IND_CODE)
		return (IND_SIZE);
	else if (arg == DIR_CODE)
	{
		if ((inst_code >= 10 && inst_code <= 12) || inst_code >= 14)
			return (IND_SIZE);
		else
			return (DIR_SIZE);
	}
	else
		return (0);
}

int	get_arg_value(t_inst instruct, unsigned char *arena, t_car *car, int arg)
{
	int	pos;

	if (arg == 1)
		pos = (car->pos + 2) % MEM_SIZE;
	else if (arg == 2)
		pos = (car->pos + 2 + instruct.sizes[0]) % MEM_SIZE;
	else
		pos = (car->pos + 2 + instruct.sizes[0] + instruct.sizes[1]) % MEM_SIZE;
	if (instruct.types[arg - 1] == DIR_CODE)
		return (n_bytes_to_int(arena, pos, instruct.sizes[arg - 1]));
	else if (instruct.types[arg - 1] == REG_CODE)
	{
		if (arena[pos] > 0 && arena[pos] <= REG_NUMBER)
			return (car->registry[arena[pos] - 1]);
		return (0);
	}
	else
		return (n_bytes_to_int(arena, pos, instruct.sizes[arg - 1]));
}
