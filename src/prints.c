/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:41:26 by rkyttala          #+#    #+#             */
/*   Updated: 2022/07/22 16:36:53 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_live(int car_id, t_champ champ)
{
	ft_printf("A process shows that player %d (%s) is alive\n", \
	car_id, \
	champ.playernbr, \
	champ.name \
	);
}

/*
** checks arg type, validates registry number. if these are valid, prints the
** value stored in the registry indicated by two bytes after car->pos.
** returns the amount of bytes for the carriage to move forward, which is
** two (= instruction + arg_code) + arg_size.
*/
int	print_aff(t_car *car, unsigned char *arena)
{
	int				type;
	int				reg;
	unsigned int	value;

	type = get_arg_type(arena[(car->pos + 1) % MEM_SIZE], 1);
	if (!type)
		return (2);
	else if (type == DIR_CODE)
		return (2 + DIR_SIZE);
	else if (type == IND_CODE)
		return (2 + IND_SIZE);
	reg = arena[(car->pos + 2) % MEM_SIZE];
	if (reg < 1 || reg > REG_NUMBER)
		return (2 + T_REG);
	value = car->registry[reg - 1];
	ft_putchar((char)((value & 0xff000000) >> 24));
	ft_putchar((char)((value & 0xff0000) >> 16));
	ft_putchar((char)((value & 0xff00) >> 8));
	ft_putchar((char)(value & 0xff));
	return (2 + T_REG);
}

void	print_usage(void)
{
	ft_printf("Usage: \
	\n./corewar [-dump N] [-s N] [-v N] [[-n N] <champion1.cor> <...>]\
	\n\n************************************************************\
	\n\n%4s: executes up to N cycles after which memory is dumped to STDOUT\
	\n%4s: N [1...%i] assigns the following champion's player number\
	\n%4s: dumps memory after every N cycles\
	\n%4s: verbose level [1...3], prints various events during execution\n\n", \
	"dump", "n", MAX_PLAYERS, "s", "v");
	exit(-9);
}

/*
** prints an error message based on @errno and exits the program.
** if @filepath is not NULL, it's contents will be appended to @message.
**
** @errno: a negative int
**	-1: "Error opening file"
**	-2: "Error reading file" (either read() failed or too few bytes were read)
**	-3: "Unknown filetype header"
**	-4: "Champion name too long"
**	-5: "Champion weighs too much"
**	-6: "Champion comment too long"
**	-7: "Player number higher than champ_count"
**	-8: "Out of memory"
**
** @path: the path to the file that could not be opened
** @champ: pointer to the champ that caused the error
*/
void	print_error(int errno, const char *path, t_champ *champ)
{
	if (errno == -1)
		ft_printf("ERROR: failed to open file: %s\n", path);
	else if (errno == -2)
		ft_printf("ERROR: failed to read file: %s\n", path);
	else if (errno == -3)
		ft_printf("ERROR: Unknown filetype header in file \"%s\": %p\n", \
		path, champ->magic);
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
		ft_printf("ERROR: Invalid player number given for '%s':\n%s\n", \
		champ->name, "Number can't be greater than champion count");
	else
		ft_printf("ERROR: OOM\n");
	exit(errno);
}
