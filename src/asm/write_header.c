/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:52:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/26 19:45:14 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	write_header(t_data *data)
{
	int32_t	magic;

	magic = COREWAR_EXEC_MAGIC;
	write(data->target_fd, &magic, 4);
	// magic = COREWAR_EXEC_MAGIC >> 16;
	// write(data->target_fd, &magic, 2);
	// magic = COREWAR_EXEC_MAGIC;
	// write(data->target_fd, &magic, 2);
}
