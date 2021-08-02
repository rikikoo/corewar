/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/02 16:36:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** sorts champions according to -n flags given in the program arguments
**
** @champs: array of champions
** @champ_count: the total number of champions
*/
void	sort_champs(t_champ *champs, int champ_count)
{
	int		p;
	t_champ	tmp;

	p = champ_count;
	while (--p >= 0)
	{
		if (champs[p].playernbr != -1)
		{
			if (champs[p].playernbr > champ_count)
				print_error(-7, NULL, &champs[p]);
			if (champs[p].playernbr - 1 != p)
			{
				tmp = champs[champs[p].playernbr - 1];
				champs[champs[p].playernbr - 1] = champs[p];
				champs[p] = tmp;
			}
		}
		champs[p].playernbr = p + 1;
	}
}

static int	validate_champ(t_champ champ)
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
** @flags: pointer to a t_flags struct
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
	if (ret == -1)
		print_error(-2, filepath, NULL);
	champ.magic = ft_bytes_toint(buf, 4);
	ft_memcpy(champ.name, &buf[4], PROG_NAME_LENGTH);
	champ.size = ft_bytes_toint(&buf[PROG_NAME_LENGTH + 8], 4);
	ft_memcpy(champ.comment, &buf[PROG_NAME_LENGTH + 12], COMMENT_LENGTH);
	ft_memcpy(champ.exec, &buf[PROG_NAME_LENGTH + COMMENT_LENGTH + 16], \
	champ.size);
	champ.playernbr = flags->playernbr;
	flags->champ_count++;
	ret = validate_champ(champ);
	if (ret < 0)
		print_error(ret, filepath, &champ);
	return (champ);
}
