/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/24 18:00:35 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	dump_memory(const unsigned char *buf, const int cycles)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	row_len = 31;
	j = row_len;
	while (i < cycles)
	{
		if (buf[i] >= 0 && buf[i] < 10)
			ft_printf("0");
		ft_printf("%x", buf[i]);
		if (i == j)
		{
			ft_printf("\n");
			j = j + row_len + 1;
		}
		else if (i % 2 != 0 && i != 0)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n%d\n", i);
}

/*
** prints usage in case an invalid flag was encountered
*/
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
** prints passed error message when called and exits the program.
** if @filepath is not NULL, it's contents will be appended to @message.
**
** @message: a string containing the desired error message
** @filepath: the path to the file that could not be opened as a string
*/
void	print_error(const char *message, const char *filepath)
{
	if (filepath)
		ft_printf("%s: %s\n", message, filepath);
	else
		ft_printf("%s\n", message);
	exit(-1);
}
