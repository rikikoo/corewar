/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:35:04 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/17 15:26:39 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_labels(t_statement *head)
{
	t_statement	*cur;
	int			i;

	cur = head;
	while (cur != NULL)
	{
		i = 0;
		while (i < 3 && cur->argtypes[i])
		{
			if (cur->arg[i][0] == DIRECT_CHAR && cur->arg[i][1] == LABEL_CHAR)
				find_label_pos(&head, cur->arg[i] + 2);
			else if (cur->arg[i][0] == LABEL_CHAR)
				find_label_pos(&head, cur->arg[i] + 1);
			i++;
		}
		cur = cur->next;
	}
}
