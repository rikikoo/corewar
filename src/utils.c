/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:30:39 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/21 22:46:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

/*
** prints usage to STDOUT and STDERR in case an invalid flag was encountered
*/
void	print_usage(void)
{
	ft_printf("Usage: \
	./corewar [-dump N] [-a] [[-n nbr] <champion1.cor> <...>]\n \
	\n************************************************************\n \
	dump: executes up to N cycles after which the arena is dumped to STDOUT \
	\n   a: use this to print the 'aff' instruction's contents during corewar \
	\n   n: nbr [1...%i] assigns the following champions player number\n \
	\n************************************************************\n \
	\n   s: TBD\n   v: TBD\n", MAX_PLAYERS);
	ft_putstr_fd("corewar launched with invalid flags. \
	Usage printed to STDOUT.\nExit code: 1.\n", 2);
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
