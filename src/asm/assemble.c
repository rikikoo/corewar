/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:17:29 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 15:09:03 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_debug(t_statement **head) // DELETE
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
		ft_printf("	%s, 0x%x\n", c->op_name, c->op_code);
		c = c->next;
	}
}

void	assemble(char *filename)
{
	t_data		*data;
	t_statement	*list;

	data = init_data(filename);
	list = init_list();
	read_file(data, list, NULL, 0);
	print_debug(&list); // DELETE
	write_file(data);
	free_data(data);
	free_list(&list);
}
