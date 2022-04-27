/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:52:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/27 14:29:49 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static void	write_champion_comment(t_data *data)
{
	size_t		i;
	u_int8_t	zero;

	i = 0;
	while (i < ft_strlen(data->comment))
	{
		write(data->target_fd, &data->comment[i], 1);
		i++;
	}
	zero = 0;
	while (i < COMMENT_LENGTH)
	{
		write(data->target_fd, &zero, 1);
		i++;
	}
}

static void	write_null(int fd)
{
	u_int32_t	zero;

	zero = 0;
	write(fd, &zero, 4);
}

static void	write_champion_name(t_data *data)
{
	size_t		i;
	u_int8_t	zero;

	i = 0;
	while (i < ft_strlen(data->name))
	{
		write(data->target_fd, &data->name[i], 1);
		i++;
	}
	zero = 0;
	while (i < PROG_NAME_LENGTH)
	{
		write(data->target_fd, &zero, 1);
		i++;
	}
}

static void	write_magic_header(int fd)
{
	u_int32_t	magic;

	magic = u_int_32_to_big_endian(COREWAR_EXEC_MAGIC);
	write(fd, &magic, 4);
}

void	write_header(t_data *data)
{
	write_magic_header(data->target_fd);
	write_champion_name(data);
	write_null(data->target_fd);
	// // write_exec_size(data);
	write_champion_comment(data);
	write_null(data->target_fd);
}
