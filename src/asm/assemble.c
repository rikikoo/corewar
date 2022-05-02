/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:17:29 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/02 19:23:37 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// static void	print_labels(t_statement **head)
// {
// 	t_statement	*c;
// 	t_label		*l;

// 	c = *head;
// 	while (c != NULL)
// 	{
// 		l = c->label;
// 		while (l != NULL)
// 		{
// 			ft_putendl(l->label);
// 			l = l->next;
// 		}
// 		c = c->next;
// 	}
// }

void	assemble(char *filename)
{
	t_data		*data;
	t_statement	*list;

	data = init_data(filename);
	list = init_list();
	read_file(data, &list);
	// print_labels(&list);
	write_file(data);
	free_data(data);
	free_list(&list);
}
