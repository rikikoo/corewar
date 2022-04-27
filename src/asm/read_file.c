/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:46 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/27 18:32:41 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	get_comment(t_data *data, char *s, char *comment, int *type)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*type == 0)
	{
		skip_whitespace(s, &i);
		if (ft_strncmp(s + i, comment, ft_strlen(comment)))
			parser_error_exit("invalid .comment formatting", data->row, i + 1);
		if (ft_strlen(data->comment))
			parser_error_exit("multiple .comment commands", data->row, i + 1);
		i += ft_strlen(comment);
		skip_whitespace(s, &i);
		if (s[i++] != '"')
			parser_error_exit("invalid .comment, expected \"", data->row, i + 1);
	}
	j = ft_strlen(data->comment);
	while (s[i] && s[i] != '"')
	{
		if (j == COMMENT_LENGTH)
			parser_error_exit(".comment too long", data->row, i);
		data->comment[j++] = s[i++];
	}
	if (s[i] != '"')
	{
		data->comment[j] = '\n'; // CHECK HOW BINARY HANDLES THIS!
		*type = 2;
	}
	else
		*type = 0;
	if (s[i] == '"' && s[i + 1] != '\0')
		parser_error_exit("invalid character, expected EOL", data->row, i + 1);
}

static void	get_name(t_data *data, char *s, char *name, int *type)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*type == 0)
	{
		skip_whitespace(s, &i);
		if (ft_strncmp(s + i, name, ft_strlen(name)))
			parser_error_exit("invalid .name formatting", data->row, i + 1);
		if (ft_strlen(data->comment))
			parser_error_exit("multiple .name commands", data->row, i + 1);
		i += ft_strlen(name);
		skip_whitespace(s, &i);
		if (s[i++] != '"')
			parser_error_exit("invalid .name, expected \"", data->row, i + 1);
	}
	j = ft_strlen(data->name);
	while (s[i] && s[i] != '"')
	{
		if (j == PROG_NAME_LENGTH)
			parser_error_exit(".name too long", data->row, i);
		data->name[j++] = s[i++];
	}
	if (s[i] != '"')
	{
		data->name[j] = '\n'; // CHECK HOW BINARY HANDLES THIS!
		*type = 1;
	}
	else
		*type = 0;
	if (s[i] == '"' && s[i + 1] != '\0')
		parser_error_exit("invalid character, expected EOL", data->row, i + 1);
}

// since .name and .comment strings can be over multiple lines,
// variable type tracks what command is ongoing
// type == 0 is undefined
// type == 1 is for .name
// type == 2 is for .comment
// type == 3 is for other statements
void	read_file(t_data *data)
{
	char	*line;
	int		type;

	type = 0;
	while (get_next_line(data->source_fd, &line))
	{
		if (ft_strstr(line, NAME_CMD_STRING) || type == 1)
			get_name(data, line, NAME_CMD_STRING, &type);
		else if (ft_strstr(line, COMMENT_CMD_STRING) || type == 2)
			get_comment(data, line, COMMENT_CMD_STRING, &type);
		// else
		// 	tokenize_line(data, line);
		free(line);
		data->row++;
		data->col = 0;
	}
	if (close(data->source_fd) == -1)
		error_exit("Error: cannot close source file");
}
