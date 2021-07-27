/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:09:28 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/27 23:05:03 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_core	init_core(void)
{
	t_core	core;

	core.aff = 0;
	core.dump = 0;
	core.split = 0;
	core.verbose = 0;
	core.champ_count = 0;
	core.player_number = 0;
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

	// debug print start
	ft_printf("\n\nname: %s\ncomment: %s\nsize: %d\nmagic: %p\
	\nplayer number: %d\
	\ncode:\n", \
	champs[0].name, \
	champs[0].comment, \
	champs[0].size, \
	champs[0].magic, \
	champs[0].playernbr);
	dump_memory(champs[0].exec, champs[0].size);
	// debug print end

	if (core.champ_count == 0)
		print_usage();
	return (0);
}
