/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:40:08 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/27 17:16:20 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_data(t_data *data)
{
	// free(data->name);
	// free(data->comment);
	free(data->filename);
	free(data);
}
