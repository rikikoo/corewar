/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/21 23:39:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

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
	\n%4s: TBD\n",
	"dump", "a", "n",  MAX_PLAYERS, "s", "v");
	exit(1);
}

void	print_error(const char *message, const char *filepath)
{
	if (filepath)
		ft_printf("%s: %s\n", message, filepath);
	else
		ft_printf("%s\n", message);
	exit(-1);
}
