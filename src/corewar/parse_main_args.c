/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:27:54 by rkyttala          #+#    #+#             */
/*   Updated: 2022/10/06 23:01:13 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_player_number(const char *arg, t_flags *flags)
{
	int	nbr;

	nbr = ft_atoi(arg);
	if (nbr < 1 || nbr > MAX_PLAYERS || flags->used_nbrs[nbr - 1])
	{
		print_usage();
	}
	flags->used_nbrs[nbr - 1] = 1;
	return (nbr);
}

static int	get_flag_cycles(const char *arg)
{
	int	cycles;

	cycles = ft_atoi(arg);
	if (cycles < 1)
	{
		print_usage();
	}
	return (cycles);
}

/*
** checks if the passed argument is a valid flag and stores the number of
** cycles associated with it to the flags struct, also passed to this function
**
** @argv: vector of the program's arguments
** @count: pointer to the index of the current argument in argv
** @flags: pointer to a t_flags struct
*/
static void	store_flag(char **argv, int *count, t_flags *flags)
{
	if (ft_strequ(argv[*count], "-dump"))
		flags->dump = get_flag_cycles(argv[++(*count)]);
	else if (ft_strequ(argv[*count], "-v"))
		flags->verbose = get_flag_cycles(argv[++(*count)]);
	else if (ft_strequ(argv[*count], "-n"))
		flags->playernbr = get_player_number(argv[++(*count)], flags);
	else if (ft_strequ(argv[*count], "-l"))
		flags->row_len = flags->row_len + (32 * (flags->row_len == 32));
	else
		print_usage();
}

/*
** loops through all args. if a '-' is encountered, the argument is sent to
** store_flag(), otherwise to read_cor(). flags must be separate,
** e.g.
** 		-v -n 4 	-- allowed
** 		-vn 4		-- not allowed
**		-n4			-- not allowed
**
** @ac: program argument count
** @av: program argument vector
** @flags: pointer to a t_flags struct
** @champs: pointer to an array of t_champs
*/
void	parse_args(int ac, char **av, t_flags *flags, t_champ *champs)
{
	int	count;
	int	playernbr;

	count = 0;
	playernbr = 0;
	while (++count < ac)
	{
		if (av[count][0] == '-')
		{
			if (count + 1 < ac)
				store_flag(av, &count, flags);
			else
				print_usage();
		}
		else if (playernbr < MAX_PLAYERS && ft_strlen(av[count]) > 4 && \
		ft_strequ(&av[count][ft_strlen(av[count]) - 4], ".cor"))
		{
			champs[playernbr] = read_cor(av[count], flags);
			playernbr++;
			flags->playernbr = -1;
		}
		else
			print_usage();
	}
}
