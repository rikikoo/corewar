/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:17:29 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/05 16:27:35 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_debug(t_statement **head, t_data *data) // DELETE
{
	t_statement	*c;
	t_label		*l;

	c = *head;
	while (c != NULL)
	{
		l = c->label;
		while (l != NULL)
		{
			ft_printf("%s, pos:%d\n", l->label, l->pos);
			l = l->next;
		}
		ft_printf("	%s, 0x%02x", c->op_name, c->op_code);
		int i = 0;
		while (c->argtypes[i])
		{
			if (i == 0)
				ft_printf(": %s", c->arg[i]);
			else
				ft_printf(", %s", c->arg[i]);
			i++;
		}
		ft_printf(" - pos: %d", c->pos);
		ft_printf("\n");
		c = c->next;
	}
	ft_printf("\nchamp_size: %d\n", data->champ_size);
}

void	assemble(char *filename)
{
	t_data		*data;
	t_statement	*list;

	data = init_data(filename);
	list = init_list();
	read_file(data, list, NULL, 0);
	print_debug(&list, data); // DELETE
	write_file(data, list);
	free_data(data);
	free_list(&list);
}
