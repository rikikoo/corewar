/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/29 19:47:03 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** treats the byte pointed to by @bytes as the most significant byte of a
** series of four bytes forward.
*/
static unsigned int	four_bytes_toint(const unsigned char *bytes)
{
	unsigned int	nb;

	nb = (unsigned int)bytes[0] << 24;
	nb += (unsigned int)bytes[1] << 16;
	nb += (unsigned int)bytes[2] << 8;
	nb += (unsigned int)bytes[3];
	return (nb);
}

static int	validate_champ(t_champs champ)
{
	if (champ.magic != COREWAR_EXEC_MAGIC)
		return (-3);
	if (ft_strlen(champ.name) > PROG_NAME_LENGTH)
		return (-4);
	if (champ.size > CHAMP_MAX_SIZE)
		return (-5);
	if (ft_strlen(champ.comment) > COMMENT_LENGTH)
		return (-6);
	return (0);
}

/*
** reads MEM_SIZE bytes from the .cor file to a stack buffer and copies
** chunks of predetermined length to a champ struct.
** returns the filled champ upon successful reading and parsing.
** calls print_error() if data isn't valid.
**
** @filepath: path to the .cor file
** @core: pointer to a t_core struct
*/
t_champs	read_cor(const char *filepath, t_core *core)
{
	int				fd;
	t_champs		champ;
	unsigned char	buf[MEM_SIZE];
	int				ret;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		print_error(-1, filepath, NULL);
	ret = read(fd, &buf, MEM_SIZE);
	close(fd);
	if (ret == -1)
		print_error(-2, filepath, NULL);
	champ.magic = four_bytes_toint(buf);
	ft_memcpy(champ.name, &buf[4], PROG_NAME_LENGTH);
	champ.size = four_bytes_toint(&buf[PROG_NAME_LENGTH + 8]);
	ft_memcpy(champ.comment, &buf[PROG_NAME_LENGTH + 12], COMMENT_LENGTH);
	ft_memcpy(champ.exec, &buf[PROG_NAME_LENGTH + COMMENT_LENGTH + 16], \
	champ.size);
	champ.playernbr = core->playernbr;
	core->champ_count++;
	ret = validate_champ(champ);
	if (ret < 0)
		print_error(ret, filepath, &champ);
	return (champ);
}
