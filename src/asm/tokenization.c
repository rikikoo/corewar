/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:44:11 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 15:11:14 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	get_args(t_data *data, t_statement *cur, char *s)
{
	
}

// data->col isn't updated before return for better error messages
// before return data->col skips possible whitespaces to the
// beginning of first argument
static void	get_op(t_data *data, t_statement *cur, char *s)
{
	size_t	i;
	char	*op;

	i = data->col;
	while (s[i] && s[i] != ' ' && s[i] != DIRECT_CHAR)
		i++;
	if (s[i] != ' ' && s[i] != DIRECT_CHAR)
		parser_error_exit("invalid character after operation name",
			data->row, i + 1);
	cur->op_name = ft_strsub(s, data->col, i - data->col);
	cur->op_code = assign_op_code(data, cur->op_name);
	data->col = i;
	skip_whitespace(s, &data->col);
}

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
// if it's a label return it, otherwise return NULL
// on NULL sets data->col to beginning of statement after whitespaces
// on label return sets data->col to after LABEL_CHAR
static char	*get_label(t_data *data, char *s)
{
	size_t	i;
	size_t	start;

	i = data->col;
	while (s[i] && s[i] != LABEL_CHAR)
		i++;
	if (s[i] == LABEL_CHAR)
	{
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

// makes new linked list node if valid line and tail node has
// an operation name saved already, then moves cur to tail node
// saves op_name, op_code and args to the node
void	tokenize_line(t_data *data, t_statement *cur, char *s)
{
	char		*label;

	if (data->comment[0] == '\0' || data->name[0] == '\0')
		parser_error_exit("expected .name or .comment", data->row, 1);
	if (s[data->col] == '.')
		parser_error_exit("unexpected comment", data->row, data->col + 1);
	label = get_label(data, s);
	if (label)
		save_label(label, cur);
	skip_whitespace(s, &data->col);
	if (!s[data->col])
		return ;
	get_op(data, cur, s);
	get_args(data, cur, s);
}
