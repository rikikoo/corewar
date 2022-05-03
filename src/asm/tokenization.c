/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:44:11 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 11:21:55 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	save_label(char *label, t_statement *cur)
{
	size_t	i;
	t_label	*tmp;

	append_labels(&cur->label);
	tmp = cur->label;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->label = label;
}

// finds label char if present in line
// checks if it's a label or argument
// if it's a label return it, otherwise NULL
// on NULL sets data->col to beginning of statement after whitespaces
// on label return sets data->col to after LABEL_CHAR
static char	*get_label(t_data *data, char *s)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (s[i] && s[i] != LABEL_CHAR)
		i++;
	if (s[i] == LABEL_CHAR)
	{
		skip_whitespace(s, &data->col);
		if (data->col == i)
			parser_error_exit("empty label", data->row, data->col);
		start = data->col;
		while (data->col < i && is_label_char(s[data->col]))
			data->col++;
		if (data->col != i)
		{
			data->col = start;
			return (NULL);
		}
		data->col = i + 1;
		return (ft_strsub(s, start, data->col - 1 - start));
	}
	return (NULL);
}

void	tokenize_line(t_data *data, t_statement *cur, char *s, int *type)
{
	char		*label;

	label = get_label(data, s);
	if (label)
		save_label(label, cur);
	skip_whitespace(s, &data->col);
	append_list(&cur);
}
