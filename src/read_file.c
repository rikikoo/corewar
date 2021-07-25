/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/24 18:07:03 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	parse_champ(int fd, t_core *core, t_champs *champ)
{
	unsigned char	buf[CHAMP_MAX_SIZE];

	if (read(fd, &buf, CHAMP_MAX_SIZE) == 0)
		ft_printf("reading to buf successful\n");

	// dump buffer for debugging
	dump_memory(&buf[136], 325);

	core->champ_count++;
	champ->size = 1;
	return (0);
}

t_champs	*read_cor(const char *filepath, t_core *core)
{
	int	fd;
	t_champs	*champ;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		print_error("Unable to read file", filepath);
	champ = (t_champs *)malloc(sizeof(t_champs));
	if (!champ)
		return (NULL);
	champ->size = 0;
	champ->playernbr = core->player_number;
	if (parse_champ(fd, core, champ) == -1)
	{
		free(champ);
		close(fd);
		print_error("Error reading champion", filepath);
	}
	return (champ);
}
