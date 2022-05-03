/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:53:32 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 18:22:14 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "oplist.h"

void	validate_arg_type(t_data *data, t_statement *cur, int arg_num,
int arg_type)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (cur->op_code == g_oplist[i].op_code)
			break ;
		i++;
	}
	// ft_printf("op:%s, arg_num:%d, arg_type:%d\n", cur->op_name, arg_num, arg_type);
	// ft_printf("%d\n", g_oplist[i].arg_type[arg_num]);
	if ((int)g_oplist[i].arg_type[arg_num] != \
	(int)(g_oplist[i].arg_type[arg_num] | arg_type))
		parser_error_exit("invalid argument type", data->row, data->col + 1);
}

void	save_label(char *label, t_statement *cur)
{
	size_t	i;
	t_label	*tmp;

	append_labels(&cur->label);
	tmp = cur->label;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->label = label;
}

u_int8_t	assign_op_code(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(s, g_oplist[i].op_name))
			return (g_oplist[i].op_code);
		i++;
	}
	parser_error_exit("invalid operation name", data->row, data->col + 1);
}

int	is_label_char(char s)
{
	size_t	i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (s == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}
