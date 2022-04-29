/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:46 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/28 14:40:19 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

t_data	*init_data(char *filename)
{
	t_data	*data;
	char	*tmp;

	data = (t_data *)malloc_safe(sizeof(t_data));
	data->source_fd = open(filename, O_RDONLY);
	if (data->source_fd == -1)
		error_exit("Error: cannot open file");
	tmp = ft_strsub(filename, 0, ft_strlen(filename) - 2);
	data->filename = ft_strjoin(tmp, ".cor");
	free(tmp);
	return (data);
}