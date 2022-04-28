/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:45:27 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/28 14:46:40 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_for_newline_at_the_end_of_file(t_data *data)
{
	char	buf[1];

	lseek(data->source_fd, -1, SEEK_END);
	read(data->source_fd, &buf, 1);
	if (buf[0] != '\n')
	{
		parser_error_exit("no newline at the end of file",
			data->row, data->col);
	}
}
