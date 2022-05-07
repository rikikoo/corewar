/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:46 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 14:29:24 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void	append_labels(t_label **head)
{
	t_label	*cur;

	if (*head == NULL)
		*head = (t_label *)malloc_safe(sizeof(t_label));
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = (t_label *)malloc_safe(sizeof(t_label));
	}
}

void	append_list(t_statement **head)
{
	t_statement	*cur;

	cur = *head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = (t_statement *)malloc_safe(sizeof(t_statement));
}

t_statement	*init_list(void)
{
	t_statement	*node;

	node = (t_statement *)malloc_safe(sizeof(t_statement));
	return (node);
}

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
