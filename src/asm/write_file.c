/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:35:13 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/26 19:34:53 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	write_file(t_data *data)
{
	data->target_fd = open(data->filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (data->target_fd == -1)
		error_exit("Error: cannot open output file");
	write_header(data);
}
