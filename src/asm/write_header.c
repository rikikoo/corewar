/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:52:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/27 18:16:34 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	write_exec_size(t_data *data)
{
	u_int32_t	val;

	val = u_int_32_to_big_endian(data->champ_size);
	write(data->target_fd, &val, 4);
}

void	write_champion_comment(t_data *data)
{
	size_t		i;

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		write(data->target_fd, &data->comment[i], 1);
		i++;
	}
}

void	write_null(int fd)
{
	u_int32_t	zero;

	zero = 0;
	write(fd, &zero, 4);
}

void	write_champion_name(t_data *data)
{
	size_t		i;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		write(data->target_fd, &data->name[i], 1);
		i++;
	}
}

void	write_magic_header(int fd)
{
	u_int32_t	magic;

	magic = u_int_32_to_big_endian(COREWAR_EXEC_MAGIC);
	write(fd, &magic, 4);
}
