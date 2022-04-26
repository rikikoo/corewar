/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:17:29 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/26 16:34:57 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	assemble(char *filename)
{
	t_data	*data;

	data = init_data(filename);
	read_file(data);
	write_file(data);
	free_data(data);
}
