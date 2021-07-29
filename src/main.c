/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:09:28 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/29 19:47:09 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_core	init_core(void)
{
	t_core	core;
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		core.used_nbrs[i] = 0;
		i++;
	}
	core.aff = 0;
	core.dump = 0;
	core.split = 0;
	core.verbose = 0;
	core.champ_count = 0;
	core.playernbr = -1;
	core.program_counter = 0x0;
	core.carry = 0;
	return (core);
}

int	main(int argc, char **argv)
{
	t_core		core;
	t_champs	champs[MAX_PLAYERS];

	if (argc == 1)
		print_usage();
	core = init_core();
	parse_args(argc, argv, &core, champs);
	if (core.champ_count == 0)
		print_usage();
	sort_champs(champs, core.champ_count);

	// debug print start
	for (int i = 0; i < core.champ_count; i++) {
		ft_printf("\n\nname: %s\ncomment: %s\nsize: %d\nmagic: %p\
		\nplayer number: %d\ncode:\n", \
		champs[i].name, \
		champs[i].comment, \
		champs[i].size, \
		champs[i].magic, \
		champs[i].playernbr);
		dump_memory(champs[i].exec, champs[i].size);
	}
	// debug print end

	return (0);
}
