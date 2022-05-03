/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:18:32 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 18:17:15 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_label(t_data *data, t_statement *cur, char *s)
{
	size_t	start;
	size_t	end;
	char	*ret;

	start = data->col;
	while (is_label_char(s[data->col]))
		data->col++;
	end = data->col;
	skip_whitespace(s, &data->col);
	if (s[data->col] != '\0' && s[data->col] != SEPARATOR_CHAR)
		parser_error_exit("invalid label", data->row, data->col + 1);
	ret = ft_strsub(s, start - 2, end - start + 2);
	ret[0] = DIRECT_CHAR;
	ret[1] = LABEL_CHAR;
	return (ret);
}

void	get_t_dir_arg(t_data *data, t_statement *cur, int arg_num, char *s)
{
	size_t	len;
	size_t	start;

	len = 1;
	data->col++;
	skip_whitespace(s, &data->col);
	if (s[data->col] == LABEL_CHAR)
	{
		len++;
		data->col++;
	}
	skip_whitespace(s, &data->col);
	if (len == 2)
		cur->arg[arg_num] = get_label(data, cur, s);
	else
	{
		start = data->col;
		if (s[data->col] == '-')
			data->col++;
		while (ft_isdigit(s[data->col]))
			data->col++;
		cur->arg[arg_num] = ft_strsub(s, start - 1, data->col - start + 1);
		cur->arg[arg_num][0] = DIRECT_CHAR;
	}
	cur->argtypes[arg_num] = T_DIR;
	skip_whitespace(s, &data->col);
	if (s[data->col] != '\0' && s[data->col] != SEPARATOR_CHAR)
		parser_error_exit("expected SEPARATOR or EOL",
			data->row, data->col + 1);
}

// returns T_REG arg
// moves data->row to beginning of next argument or EOL
// if it doesn't find next argument or EOL, outputs error
void	get_t_reg_arg(t_data *data, t_statement *cur, int arg_num, char *s)
{
	size_t	start;
	size_t	end;
	int		reg;

	start = data->col;
	data->col++;
	if (!ft_isdigit(s[data->col]))
		parser_error_exit("invalid REG_NUMBER", data->row, data->col + 1);
	reg = ft_atoi(s + data->col);
	if (reg == 0)
		parser_error_exit("REG_NUMBER 0", data->row, data->col + 1);
	while (ft_isdigit(s[data->col]))
		data->col++;
	end = data->col;
	skip_whitespace(s, &data->col);
	if (s[data->col] != '\0' && s[data->col] != SEPARATOR_CHAR)
		parser_error_exit("expected SEPARATOR or EOL",
			data->row, data->col + 1);
	cur->arg[arg_num] = ft_strsub(s, start, end - start);
	cur->argtypes[arg_num] = T_REG;
}
