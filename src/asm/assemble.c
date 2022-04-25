/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:17:29 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/25 16:42:28 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	assemble(char *filename)
{
	int			fd;
	t_commands	*commands;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Error: Cannot open file");
	commands = init_parser(fd);
	free_commands(commands);
}
