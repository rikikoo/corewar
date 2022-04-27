/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:35:13 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/27 14:56:53 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	write_header(t_data *data)
{
	write_magic_header(data->target_fd);
	write_champion_name(data);
	write_null(data->target_fd);
	write_exec_size(data);
	write_champion_comment(data);
	write_null(data->target_fd);
}

void	write_file(t_data *data)
{
	data->target_fd = open(data->filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (data->target_fd == -1)
		error_exit("Error: cannot open output file");
	write_header(data);
	if (close(data->target_fd) == -1)
		error_exit("Error: cannot close output file");
}
