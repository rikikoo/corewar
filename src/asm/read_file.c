/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:46 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/28 14:44:33 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

static char	*validate_command_end(t_data *data, char *s, char *cmd, int *type)
{
	if (s[data->col] != '"')
	{
		if (ft_strequ(cmd, ".name"))
			*type = 1;
		else if (ft_strequ(cmd, ".command"))
			*type = 2;
		return (NULL);
	}
	if (s[data->col] == '"')
	{
		data->col++;
		skip_whitespace(s, &data->col);
		if (s[data->col] != '\0')
			return (ft_strjoin("epected EOL, invalid ", cmd));
	}
	*type = 0;
	return (NULL);
}

static char	*validate_command_start(t_data *data, char *s, char *cmd)
{
	skip_whitespace(s, &data->col);
	if (ft_strncmp(s + data->col, cmd, ft_strlen(cmd)))
		return (ft_strjoin("invalid formatting of ", cmd));
	if (ft_strlen(data->comment))
		return (ft_strjoin("multiple commands of type ", cmd));
	data->col += ft_strlen(cmd);
	skip_whitespace(s, &data->col);
	if (s[data->col++] != '"')
		return (ft_strjoin("expected '\"', invalid formatting of ", cmd));
	return (NULL);
}

static void	get_comment(t_data *data, char *s, char *comment, int *type)
{
	size_t	j;
	char	*error;

	if (*type == 0)
	{
		error = validate_command_start(data, s, comment);
		if (error != NULL)
			parser_error_exit(error, data->row, data->col + 1);
	}
	j = ft_strlen(data->comment);
	while (s[data->col] && s[data->col] != '"')
	{
		if (j == COMMENT_LENGTH)
			parser_error_exit(".comment too long", data->row, data->col);
		data->comment[j++] = s[data->col++];
	}
	if (s[data->col] != '"')
		data->comment[j] = '\n'; // CHECK HOW BINARY HANDLES THIS!
	error = validate_command_end(data, s, comment, type);
	if (error != NULL)
		parser_error_exit(error, data->row, data->col + 1);
}

static void	get_name(t_data *data, char *s, char *name, int *type)
{
	size_t	j;
	char	*error;

	if (*type == 0)
	{
		error = validate_command_start(data, s, name);
		if (error != NULL)
			parser_error_exit(error, data->row, data->col + 1);
	}
	j = ft_strlen(data->name);
	while (s[data->col] && s[data->col] != '"')
	{
		if (j == PROG_NAME_LENGTH)
			parser_error_exit(".name too long", data->row, data->col);
		data->name[j++] = s[data->col++];
	}
	if (s[data->col] != '"')
		data->name[j] = '\n'; // CHECK HOW BINARY HANDLES THIS!
	error = validate_command_end(data, s, name, type);
	if (error != NULL)
		parser_error_exit(error, data->row, data->col + 1);
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
		data->row++;
		data->col = 0;
		if (ft_strstr(line, NAME_CMD_STRING) || type == 1)
			get_name(data, line, NAME_CMD_STRING, &type);
		else if (ft_strstr(line, COMMENT_CMD_STRING) || type == 2)
			get_comment(data, line, COMMENT_CMD_STRING, &type);
		// else
		// 	tokenize_line(data, line);
		free(line);
	}
	check_for_newline_at_the_end_of_file(data);
	char	buf[1];
	
	lseek(data->source_fd, -1, SEEK_END);
	read(data->source_fd, &buf, 1);
	if (buf[0] != '\n')
		parser_error_exit("no newline at the end of file", data->row, data->col);
	if (close(data->source_fd) == -1)
		error_exit("Error: cannot close source file");
}