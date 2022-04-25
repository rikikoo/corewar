/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:46 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/25 18:51:21 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"
#include "get_next_line.h"

char	*get_name_or_comment(char *s, char *name_or_comment)
{
	char	*name;
	size_t	i;
	size_t	j;

	if (ft_strncmp(s, name_or_comment, ft_strlen(name_or_comment)))
		error_exit("Error: invalid .name or .comment formatting");
	i = 0;
	while (s[i] != '"' && s[i] != '\0')
		i++;
	if (s[i] != '"')
		error_exit("Error: invalid .name or .comment");
	j = i + 1;
	while (s[j] != '"' && s[j] != '\0')
		j++;
	if (s[j] != '"' || s[j + 1] != '\0')
		error_exit("Error: invalid .name or .comment");
	name = ft_strsub(s, i + 1, ft_strlen(s + i + 2));
	if (ft_strequ(name_or_comment, NAME_CMD_STRING)
		&& ft_strlen(name) > PROG_NAME_LENGTH)
		error_exit("Error: .name too long");
	else if (ft_strequ(name_or_comment, COMMENT_CMD_STRING)
		&& ft_strlen(name) > COMMENT_LENGTH)
		error_exit("Error: .comment too long");
	return (name);
}

t_commands	*init_parser(int fd)
{
	t_commands	*commands;
	char		*line;

	commands = malloc_safe(sizeof(t_commands));
	while (get_next_line(fd, &line))
	{
		if (ft_strstr(line, NAME_CMD_STRING))
			commands->name = get_name_or_comment(line, NAME_CMD_STRING);
		else if (ft_strstr(line, COMMENT_CMD_STRING))
			commands->comment = get_name_or_comment(line, COMMENT_CMD_STRING);
		free(line);
	}
	return (commands);
}
