/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/29 19:57:15 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** sorts champions according to -n flags given in the program arguments
**
** @champs: array of champions
** @count: the total number of champions
*/
void	sort_champs(t_champs *champs, int count)
{
	int			p;
	t_champs	tmp;

	p = count;
	while (--p >= 0)
	{
		if (champs[p].playernbr != -1)
		{
			if (champs[p].playernbr > count)
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

/*
** prints the arena to STDOUT after a specific amount of execution cycles if the
** program was launched with the -dump flag
**
** @buf: pointer to the start of the arena
** @size: amount of bytes to print out
*/
void	dump_memory(const unsigned char *buf, const int size)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	row_len = 32;
	j = row_len - 1;
	while (i < size)
	{
		ft_printf("%02x", buf[i]);
		if (i == j)
		{
			ft_putchar('\n');
			j += row_len;
		}
		else
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	print_usage(void)
{
	ft_printf("Usage: \
	./corewar [-dump N] [-a] [[-n nbr] <champion1.cor> <...>]\
	\n\n************************************************************\
	\n\n%4s: executes up to N cycles after which memory is dumped to STDOUT\
	\n%4s: use this to print the 'aff' instruction's contents during corewar\
	\n%4s: nbr [1...%i] assigns the following champions player number\
	\n%4s: TBD\
	\n%4s: TBD\n\n", \
	"dump", "a", "n", MAX_PLAYERS, "s", "v");
	exit(1);
}

/*
** prints an error message based on @errno and exits the program.
** if @filepath is not NULL, it's contents will be appended to @message.
**
** @errno: a negative int
**	-1: "Error opening file"
**	-2: "Error reading file"
**	-3: "Unknown filetype header"
**	-4: "Champion name too long"
**	-5: "Champion weighs too much"
**	-6: "Champion comment too long"
**	-7: "Unknown opcode: {opcode}"
**	-8: "Player number higher than champ_count"
**
** @path: the path to the file that could not be opened
** @champ: pointer to the champ that caused the error
*/
void	print_error(const int errno, const char *path, t_champs *champ)
{
	if (errno == -1)
		ft_printf("ERROR: failed to open file: %s\n", path);
	else if (errno == -2)
		ft_printf("ERROR: failed to read file: s\n", path);
	else if (errno == -3)
		ft_printf("ERROR: Unknown filetype header: %p\n", champ->magic);
	else if (errno == -4)
		ft_printf("ERROR: Champion name '%s' too long: %d > %d\n", \
		champ->name, ft_strlen(champ->name), PROG_NAME_LENGTH);
	else if (errno == -5)
		ft_printf("ERROR: Champion '%s' weighs too much: %d > %d\n", \
		champ->name, champ->size, CHAMP_MAX_SIZE);
	else if (errno == -6)
		ft_printf("ERROR: Champion comment '%s' too long: %d > %d\n", \
		champ->comment, ft_strlen(champ->comment), COMMENT_LENGTH);
	else if (errno == -7)
		ft_printf("ERROR: Unknown opcode by %s: %o\n", champ->name, champ->err);
	else
		ft_printf("ERROR: Invalid player number given for '%s'\
		\nNumber can't be greater than the number of champions\n", champ->name);
	exit(errno);
}
