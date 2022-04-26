/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:46 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/26 18:36:55 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	get_comment(t_data *data, char *s, char *comment)
{
	size_t	i;
	size_t	j;

	if (ft_strncmp(s, comment, ft_strlen(comment)))
		parser_error_exit("invalid .comment formatting", data->row, 0);
	i = 0;
	while (s[i] != '"' && s[i] != '\0')
		i++;
	if (s[i] != '"')
		parser_error_exit("invalid .comment", data->row, i + 1);
	j = i + 1;
	while (s[j] != '"' && s[j] != '\0')
		j++;
	if (s[j] != '"' || s[j + 1] != '\0')
		parser_error_exit("invalid .comment", data->row, j + 1);
	data->comment = ft_strsub(s, i + 1, ft_strlen(s + i + 2));
	if (ft_strlen(data->name) > COMMENT_LENGTH)
		parser_error_exit(".comment too long", data->row, 0);
}

static void	get_name(t_data *data, char *s, char *name)
{
	size_t	i;
	size_t	j;

	if (ft_strncmp(s, name, ft_strlen(name)))
		parser_error_exit("invalid .name formatting", data->row, 0);
	i = 0;
	while (s[i] != '"' && s[i] != '\0')
		i++;
	if (s[i] != '"')
		parser_error_exit("invalid .name", data->row, i + 1);
	j = i + 1;
	while (s[j] != '"' && s[j] != '\0')
		j++;
	if (s[j] != '"' || s[j + 1] != '\0')
		parser_error_exit("invalid .name", data->row, j + 1);
	data->name = ft_strsub(s, i + 1, ft_strlen(s + i + 2));
	if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		parser_error_exit(".name too long", data->row, 0);
}

void	read_file(t_data *data)
{
	char	*line;

	while (get_next_line(data->source_fd, &line))
	{
		if (ft_strstr(line, NAME_CMD_STRING))
			get_name(data, line, NAME_CMD_STRING);
		else if (ft_strstr(line, COMMENT_CMD_STRING))
			get_comment(data, line, COMMENT_CMD_STRING);
		free(line);
		data->row++;
		data->col = 0;
	}
	if (close(data->source_fd) == -1)
		error_exit("Error: cannot close source file");
}
