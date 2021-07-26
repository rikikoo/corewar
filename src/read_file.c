/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/26 13:21:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	parse_champ(t_champs *champ)
{
	if (champ->size > CHAMP_MAX_SIZE)
		return (-4);
	return (0);
}

t_champs	read_cor(const char *filepath, t_core *core)
{
	int				fd;
	t_champs		champ;
	unsigned char	buf[MEM_SIZE];
	int				ret;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		print_error(0, filepath, NULL);
	ret = read(fd, &buf, MEM_SIZE);
	close(fd);
	if (ret == -1)
		print_error(-1, filepath, NULL);
/*
**	dump_memory(buf, ret);
*/
	champ.magic = four_bytes_toint(buf);
	ft_memcpy(champ.name, &buf[4], PROG_NAME_LENGTH);
	champ.size = four_bytes_toint(&buf[PROG_NAME_LENGTH + 8]);
	ft_memcpy(champ.comment, &buf[PROG_NAME_LENGTH + 12], COMMENT_LENGTH);
	ft_memcpy(champ.exec, &buf[PROG_NAME_LENGTH + COMMENT_LENGTH + 16], \
	champ.size);
	champ.playernbr = core->player_number;
	core->champ_count++;
	ret = parse_champ(&champ);
	if (ret < 0)
		print_error(ret, filepath, &champ);
	return (champ);
}
