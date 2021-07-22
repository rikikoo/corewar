/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:09:28 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/22 16:31:08 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** only for debugging
*/
static void	dump_core(t_core core)
{
	ft_printf("%8s: %u\n%8s: %u\n%8s: %u\n%8s: %u\n%8s: %u\n%8s: %u\n%8s: %u\
	\n%8s: %p\n", \
	"aff", core.aff, \
	"dump", core.dump, \
	"split", core.split, \
	"verbose", core.verbose, \
	"champs", core.champ_count, \
	"player #", core.player_number, \
	"carry", core.carry, \
	"PC", core.program_counter \
	);
}

static t_core	init_core(void)
{
	t_core	core;

	core.aff = 0;
	core.dump = 0;
	core.split = 0;
	core.verbose = 0;
	core.champ_count = 0;
	core.player_number = 0;
	core.carry = 0;
	core.program_counter = 0x0;
	return (core);
}

int	main(int argc, char **argv)
{
	t_core		core;
	t_champs	*champs;

	if (argc == 1)
		print_usage();
	core = init_core();
	champs = parse_args(argc, argv, &core);
	dump_core(core);
	if (!champs)
		return (-1);
	return (0);
}
