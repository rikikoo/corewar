/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:40:08 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 18:21:48 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_labels(t_label **list)
{
	t_label	*cur;
	t_label	*tmp;

	cur = *list;
	while (cur->next != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->label);
		free(tmp);
	}
	if (cur->label)
	{
		free(cur->label);
		free(cur);
	}
}

void	free_list(t_statement **head)
{
	t_statement	*cur;
	t_statement	*tmp;
	int			i;

	cur = *head;
	while (cur != NULL)
	{
		if (cur->label)
			free_labels(&cur->label);
		free(cur->op_name);
		i = 0;
		while (cur->argtypes[i])
			free(cur->arg[i++]);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	free(data->filename);
	free(data);
}
