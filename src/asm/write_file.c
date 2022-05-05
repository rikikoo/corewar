/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:35:13 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/05 16:38:35 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

static void	write_exec_code(t_statement *st, int fd)
{
	while (st->op_code)
	{
		write_statement_code(st, fd);
		if (st->arg_type_code)
			write_argument_type_code(st, fd);
		write_arguments(st, fd);
		st = st->next;
	}
}

static void	write_header(t_data *data)
{
	write_magic_header(data->target_fd);
	write_champion_name(data);
	write_null(data->target_fd);
	write_exec_size(data);
	write_champion_comment(data);
	write_null(data->target_fd);
}

void	write_file(t_data *data, t_statement *st)
{
	data->target_fd = open(data->filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (data->target_fd == -1)
		error_exit("Error: cannot open output file");
	ft_printf("Writing output to %s\n", data->filename);
	write_header(data);
	write_exec_code(st, data->target_fd);
	if (close(data->target_fd) == -1)
		error_exit("Error: cannot close output file");
}
