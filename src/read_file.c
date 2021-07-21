/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/21 22:42:15 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

t_champs	*read_cor(const char *filepath, t_core core)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		print_error("Unable to read file", filepath);
}
