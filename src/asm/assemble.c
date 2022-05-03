/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:17:29 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 11:03:10 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_labels(t_statement **head) // DELETE
{
	t_statement	*c;
	t_label		*l;

	c = *head;
	while (c != NULL)
	{
		l = c->label;
		while (l != NULL)
		{
			ft_putendl(l->label);
			l = l->next;
		}
		c = c->next;
		ft_putendl("next");
	}
}

void	assemble(char *filename)
{
	t_data		*data;
	t_statement	*list;

	data = init_data(filename);
	list = init_list();
	read_file(data, &list);
	print_labels(&list); // DELETE
	write_file(data);
	free_data(data);
	free_list(&list);
}
