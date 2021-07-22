/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/22 15:45:09 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champs	*read_cor(const char *filepath, t_core *core)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		print_error("Unable to read file", filepath);
	core->champ_count++;
	close(fd);
	return (NULL);
}
