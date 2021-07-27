/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/27 23:02:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	dump_memory(const unsigned char *buf, const int cycles)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	row_len = 32;
	j = row_len - 1;
	while (i < cycles)
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
**	 0: "Error opening file"
**	-1: "Error reading file"
**	-2: "Unknown filetype header"
**	-3: "Champion name too long"
**	-4: "Champion weighs too much"
**	-5: "Champion comment too long"
**	-6: "Unknown opcode: {opcode}"
**
** @path: the path to the file that could not be opened as a string
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
	else
		ft_printf("ERROR: Unknown opcode by %s: %o\n", champ->name, \
		champ->invalid_opcode);
	exit(errno);
}
