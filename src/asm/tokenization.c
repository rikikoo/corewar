/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:44:11 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/25 18:01:07 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "oplist.h"

// If statement has no code, i.e. only label, label points to
// byte after champ exec code and thus this function returns 0
static u_int32_t	get_operation_bytesize(t_statement *st)
{
	u_int32_t	ret;
	int			i;

	if (!st->op_code)
		return (0);
	ret = 1;
	if (st->arg_type_code)
		ret++;
	i = 0;
	while (st->argtypes[i])
	{
		if (st->argtypes[i] == T_REG)
			ret++;
		else if (st->argtypes[i] == T_DIR)
			ret += st->t_dir_size;
		else
			ret += 2;
		i++;
	}
	return (ret);
}

// switch for checking that operation gets valid argument type,
// checking valid amount of arguments, and
// saving the arguments into statement struct
static void	get_args(t_data *data, t_statement *cur, char *s, int i)
{
	if (s[data->col] == SEPARATOR_CHAR || !s[data->col])
		parser_error_exit("empty argument", data->row, data->col);
	while (s[data->col])
	{
		if (s[data->col] == 'r')
			get_t_reg_arg(data, cur, i, s);
		else if (s[data->col] == DIRECT_CHAR)
			get_t_dir_arg(data, cur, i, s);
		else if (s[data->col] == '-' || ft_isdigit(s[data->col]) || \
			s[data->col] == LABEL_CHAR)
			get_t_ind_arg(data, cur, i, s);
		else if (s[data->col] != SEPARATOR_CHAR)
			parser_error_exit("invalid argument", data->row, data->col + 1);
		else if (s[data->col] == SEPARATOR_CHAR)
		{
			if (i == 2 || i == g_oplist[cur->op_code - 1].arg_cnt - 1)
				parser_error_exit("too many arguments",
					data->row, data->col + 1);
			i++;
			data->col++;
			skip_whitespace(s, &data->col);
			if (s[data->col] == SEPARATOR_CHAR)
				parser_error_exit("empty argument", data->row, data->col);
		}
	}
}

// data->col skips possible whitespaces to the
// beginning of first argument
static void	get_op(t_data *data, t_statement *cur, char *s)
{
	size_t	start;

	if (!ft_isalpha(s[data->col]))
		parser_error_exit("invalid operation name", data->row, data->col + 1);
	start = data->col;
	while (s[data->col] && ft_isalpha(s[data->col]))
		data->col++;
	if (s[data->col] != ' ' && s[data->col] != '\t' && \
		s[data->col] != DIRECT_CHAR)
		parser_error_exit("invalid character after operation name",
			data->row, data->col + 1);
	cur->op_name = ft_strsub(s, start, data->col - start);
	assign_op_specs(data, cur);
	skip_whitespace(s, &data->col);
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

	if (data->has_name == 0)
		parser_error_exit("missing .name command", data->row, 1);
	if (data->has_comment == 0)
		parser_error_exit("missing .comment command", data->row, 1);
	if (s[data->col] == '.')
		parser_error_exit("unknown command", data->row, data->col + 1);
	label = get_label(data, s);
	if (label)
		save_label(label, cur, data->champ_size);
	skip_whitespace(s, &data->col);
	if (!s[data->col])
		return ;
	get_op(data, cur, s);
	get_args(data, cur, s, 0);
	validate_arg_amount(data, cur);
	cur->pos = data->champ_size;
	data->champ_size += get_operation_bytesize(cur);
}
