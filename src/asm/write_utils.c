/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:35:33 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/06 13:21:31 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

u_int32_t	find_label_pos(t_statement **head, char *match)
{
	t_statement	*search;
	t_label		*lab;

	search = *head;
	while (search != NULL)
	{
		lab = search->label;
		while (lab != NULL)
		{
			if (ft_strequ(match, lab->label))
				return (lab->pos);
			lab = lab->next;
		}
		search = search->next;
	}
	error_exit(ft_strjoin(ft_strjoin("Error: label '", match), "' not found"));
    return (0);
}

u_int16_t	u_int16_to_big_endian(u_int16_t n)
{
	return ((n & 0xFF00) >> 8 | (n & 0x00FF) << 8);
}

u_int32_t	u_int32_to_big_endian(u_int32_t n)
{
	return ((n & 0xFF000000) >> 24 | (n & 0x00FF0000) >> 8 | \
	(n & 0x0000FF00) << 8 | (n & 0x000000FF) << 24);
}
