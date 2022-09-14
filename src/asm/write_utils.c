/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:35:33 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/14 23:30:09 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

u_int32_t	find_label_pos(t_statement **head, char *match)
{
	t_statement	*search;
	t_label		*lab;
	char		*err;

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
	err = ft_strjoin("Error: label '", match);
	error_exit(ft_strjoin(err, "' not found"));
	exit(1);
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
