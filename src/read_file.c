/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:33:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/23 19:40:05 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h> // delete after

int	parse_champ(int fd, t_core *core, t_champs *champ)
{
	unsigned char	compare[3];
	unsigned char	buf[CHAMP_MAX_SIZE];

//	compare = NULL;

	champ->size = lseek(fd, 0, SEEK_END);
	ft_printf("Champ_size:%d\n", champ->size);
//	if (champ->size > CHAMP_MAX_SIZE)
//		print_error("Champion size over CHAMP_MAX_SIZE", NULL);
	if (champ->size < 0)
		print_error("Error reading champion", NULL);
	
	if (read(fd, &buf, champ->size) >= 0)
		ft_printf("reading to buf successful\n");
	core->champ_count++;
	for (int x = 1; x < 4; x++) {
		compare[x - 1] = buf[x];
	}
//	compare = ft_strncpy(compare, &buf[1], 3);	should return 'ea83f3'
	ft_printf("%s\n", compare);
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
	champ->magic = 0;
	champ->size = 0;
	if (parse_champ(fd, core, champ) == -1)
		return (NULL);
	core->champ_count++;
	close(fd);
	return (NULL);
}
