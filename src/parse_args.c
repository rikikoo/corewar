/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:27:54 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/28 23:10:39 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** checks whether the number associated with a flag is valid and returns it
**
** @arg: the argument after the flag (i.e. a number as a string)
** @is_playernum: true if the flag in question was n
*/
static int	get_flag_cycles(const char *arg, int is_playernum)
{
	int	cycles;

	cycles = ft_atoi(arg);
	if (cycles <= 0 || (is_playernum && cycles > MAX_PLAYERS))
	{
		print_usage();
		exit(-1);
	}
	return (cycles);
}

/*
** checks if the passed argument is a valid flag and stores the number of
** cycles associated with it to the core struct, also passed to this function
**
** @argv: vector of the program's arguments
** @count: pointer to the index of the current argument in argv
** @core: pointer to a t_core struct
*/
static void	store_flag(char **argv, int *count, t_core *core)
{
	if (ft_strequ(argv[*count], "-dump"))
		core->dump = get_flag_cycles(argv[++(*count)], 0);
	else if (ft_strequ(argv[*count], "-s"))
		core->split = get_flag_cycles(argv[++(*count)], 0);
	else if (ft_strequ(argv[*count], "-v"))
		core->verbose = get_flag_cycles(argv[++(*count)], 0);
	else if (ft_strequ(argv[*count], "-n"))
		core->playernbr = get_flag_cycles(argv[++(*count)], 1);
	else
		print_usage();
}

/*
** loops through all args. if a '-' is encountered, the argument is sent to
** store_flag(), otherwise to read_cor(). flags must be separate,
** e.g.
** 		-a -n 4 	-- allowed
** 		-an 4		-- not allowed
**		-n4			-- not allowed
**
** @ac: total number of program arguments + 1
** @av: vector of the program's arguments
** @core: pointer to a t_core struct
** @champs: pointer to an array of t_champs
*/
void	parse_args(int ac, char **av, t_core *core, t_champs *champs)
{
	int	count;
	int	playernbr;

	count = 0;
	playernbr = 0;
	while (++count < ac)
	{
		if (av[count][0] == '-')
		{
			if (av[count][1] == 'a')
				core->aff = 1;
			else if (count + 1 < ac)
				store_flag(av, &count, core);
			else
				print_usage();
		}
		else if (playernbr < MAX_PLAYERS)
		{
			champs[playernbr] = read_cor(av[count], core);
			playernbr++;
		}
		else
			print_usage();
	}
}
