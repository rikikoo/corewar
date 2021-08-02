/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/02 10:52:52 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** initializes a new carriage, i.e. appends a new t_car element to the end of
** the carriage list, whose head pointer is stored in t_game
**
** @prev_id: id of previous carriage
** @pos: carriage position on the arena
** @playernbr: champion's playernbr; determined by parent carriage's registry[0]
*/
t_car	*new_car(int prev_id, int pos, int playernbr)
{
	t_car	*car;
	int		i;

	car = (t_car *)malloc(sizeof(t_car));
	if (!car)
		return (NULL);
	car->id = prev_id + 1;
	car->pos = pos;
	car->carry = 0;
	car->cycles_since_live = 0;
	car->cycles_to_exec = 0;
	car->next_instruction = 0;
	i = 0;
	car->registry[i] = playernbr * -1;
	while (++i < REG_NUMBER)
		car->registry[i] = 0;
	car->current_opcode = 0;
	car->next = NULL;
	return (car);
}

int	get_arg_type(unsigned char byte, int arg)
{
	if (arg < 1 || arg > 3)
		return (0);
	if (arg == 1)
		return (byte & 192);
	else if (arg == 2)
		return (byte & 48);
	else
		return (byte & 12);
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
