/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2022/09/27 11:43:02 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	validate_champ(unsigned char *buf, t_champ champ, int len)
{
	if (champ.magic != COREWAR_EXEC_MAGIC)
		return (-3);
	if (champ.size > CHAMP_MAX_SIZE)
		return (-4);
	if (champ.size != (len - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16)))
		return (-5);
	if (bytes_to_int(buf, PROG_NAME_LENGTH + 4, 4) != 0)
		return (-6);
	if (bytes_to_int(buf, PROG_NAME_LENGTH + COMMENT_LENGTH + 8, 4) != 0)
		return (-7);
	return (0);
}

/*
** reads MEM_SIZE bytes from the .cor file to a stack buffer and copies
** chunks of predefined length to a champ struct.
** returns the initialized champion upon successful reading and parsing.
** calls print_error() if data isn't valid.
**
** @filepath: relative path to the .cor file
** @flags: flags struct, that contains e.g. the playernumber of the champ
*/
t_champ	read_cor(const char *filepath, t_flags *flags)
{
	int				fd;
	t_champ			champ;
	unsigned char	buf[MEM_SIZE];
	int				ret;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		print_error(-1, filepath, NULL);
	ret = read(fd, &buf, MEM_SIZE);
	close(fd);
	if (ret < PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
		print_error(-2, filepath, NULL);
	champ.magic = bytes_to_int(buf, 0, 4);
	ft_memcpy(champ.name, &buf[4], PROG_NAME_LENGTH + 1);
	champ.size = bytes_to_int(buf, PROG_NAME_LENGTH + 8, 4);
	ft_memcpy(champ.comment, &buf[PROG_NAME_LENGTH + 12], COMMENT_LENGTH + 1);
	ret = validate_champ(buf, champ, ret);
	if (ret < 0)
		print_error(ret, filepath, &champ);
	ft_memcpy(champ.exec, &buf[PROG_NAME_LENGTH + COMMENT_LENGTH + 16], \
	champ.size);
	champ.playernbr = flags->playernbr;
	flags->champ_count++;
	return (champ);
}
