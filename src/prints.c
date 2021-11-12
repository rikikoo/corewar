/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:41:26 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/12 23:57:11 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_live(t_champ champ)
{
	ft_printf("A process shows that player %d (%s) is alive\n", \
	champ.playernbr, \
	champ.name \
	);
}

/*
** checks arg type, validates registry number. if these are valid, prints the
** value stored in the registry indicated by two bytes after car->pos.
** returns the amount of bytes to move forward (2 (= instruction + arg_code) +
** arg_size).
*/
int	print_aff(t_car *car, unsigned char *arena)
{
	int	type;
	int	reg;

	type = get_arg_type(arena[(car->pos + 1) % MEM_SIZE], 1);
	if (!type)
		return (2);
	else if (type == DIR_CODE)
		return (2 + DIR_SIZE);
	else if (type == IND_CODE)
		return (2 + IND_SIZE)
	else
	{
		reg = arena[(car->pos + 1) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
			return (1);
		ft_putchar((char)car->registry[reg - 1]);
		return (2 + REG_SIZE);
	}
}

void	print_usage(void)
{
	ft_printf("Usage: \
	\n./corewar [-dump N] [[-n nbr] <champion1.cor> <...>]\
	\n\n************************************************************\
	\n\n%4s: executes up to N cycles after which memory is dumped to STDOUT\
	\n%4s: nbr [1...%i] assigns the following champion's player number\
	\n%4s: WIP\
	\n%4s: WIP\n\n", \
	"dump", "n", MAX_PLAYERS, "s", "v");
	exit(-9);
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
**	-7: "Player number higher than champ_count"
**	-8: "Out of heap memory"
**
** @path: the path to the file that could not be opened
** @champ: pointer to the champ that caused the error
*/
void	print_error(int errno, const char *path, t_champ *champ)
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
		ft_printf("ERROR: Invalid player number given for '%s'\
		\nNumber can't be greater than the number of champions\n", champ->name);
	else
		ft_printf("ERROR: Something went wrong with a malloc\n");
	exit(errno);
}
