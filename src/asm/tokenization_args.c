/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:18:32 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/04 14:24:44 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	validate_arg_end(t_data *data, char *s)
{
	skip_whitespace(s, &data->col);
	if (s[data->col] != '\0' && s[data->col] != SEPARATOR_CHAR)
		parser_error_exit("invalid label", data->row, data->col + 1);
}

static char	*get_label(t_data *data, t_statement *cur, char *s, int t_dir)
{
	size_t	start;
	char	*ret;

	data->col++;
	skip_whitespace(s, &data->col);
	start = data->col;
	while (is_label_char(s[data->col]))
		data->col++;
	if (t_dir)
	{
		ret = ft_strsub(s, start - 2, data->col - start + 2);
		ret[0] = DIRECT_CHAR;
		ret[1] = LABEL_CHAR;
	}
	else
	{
		ret = ft_strsub(s, start - 1, data->col - start + 1);
		ret[0] = LABEL_CHAR;
	}
	return (ret);
}

void	get_t_ind_arg(t_data *data, t_statement *cur, int arg_num, char *s)
{
	size_t	start;

	validate_arg_type(data, cur, arg_num, T_IND);
	if (s[data->col] == LABEL_CHAR)
		cur->arg[arg_num] = get_label(data, cur, s, 0);
	else
	{
		start = data->col;
		if (s[data->col] == '-')
			data->col++;
		while (ft_isdigit(s[data->col]))
			data->col++;
		cur->arg[arg_num] = ft_strsub(s, start, data->col - start);
	}
	validate_arg_end(data, s);
	cur->argtypes[arg_num] = T_IND;
}

void	get_t_dir_arg(t_data *data, t_statement *cur, int arg_num, char *s)
{
	size_t	start;

	validate_arg_type(data, cur, arg_num, T_DIR);
	data->col++;
	skip_whitespace(s, &data->col);
	if (s[data->col] == LABEL_CHAR)
		cur->arg[arg_num] = get_label(data, cur, s, 1);
	else
	{
		skip_whitespace(s, &data->col);
		start = data->col;
		if (s[data->col] == '-')
			data->col++;
		while (ft_isdigit(s[data->col]))
			data->col++;
		cur->arg[arg_num] = ft_strsub(s, start - 1, data->col - start + 1);
		cur->arg[arg_num][0] = DIRECT_CHAR;
	}
	validate_arg_end(data, s);
	cur->argtypes[arg_num] = T_DIR;
}

// returns T_REG arg
// moves data->row to beginning of next argument or EOL
// if it doesn't find next argument or EOL, outputs error
void	get_t_reg_arg(t_data *data, t_statement *cur, int arg_num, char *s)
{
	size_t	start;
	int		reg;

	validate_arg_type(data, cur, arg_num, T_REG);
	start = data->col;
	data->col++;
	if (!ft_isdigit(s[data->col]))
		parser_error_exit("invalid REG_NUMBER", data->row, data->col + 1);
	reg = ft_atoi(s + data->col);
	if (reg == 0)
		parser_error_exit("REG_NUMBER 0", data->row, data->col + 1);
	while (ft_isdigit(s[data->col]))
		data->col++;
	cur->arg[arg_num] = ft_strsub(s, start, data->col - start);
	validate_arg_end(data, s);
	cur->argtypes[arg_num] = T_REG;
}
