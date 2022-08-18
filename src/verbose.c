/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:41:28 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/18 21:03:28 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_arg_types(unsigned char *arena, t_car *car, t_inst instruct)
{
	int	i;

	i = 0;
	ft_printf("(ACB: %#2x", arena[(car->pos + 1) % MEM_SIZE]);
	ft_printf(" [ ");
	while (instruct.types[i] && i < 4)
	{
		ft_printf("%d ", instruct.types[i]);
		i++;
	}
	ft_printf("])");
}

static char	*get_inst_name(int inst_code)
{
	if (inst_code == 2)
		return ("ld");
	else if (inst_code == 3)
		return ("st");
	else if (inst_code == 4)
		return ("add");
	else if (inst_code == 5)
		return ("sub");
	else if (inst_code == 6)
		return ("and");
	else if (inst_code == 7)
		return ("or");
	else if (inst_code == 8)
		return ("xor");
	else if (inst_code == 10)
		return ("ldi");
	else if (inst_code == 11)
		return ("sti");
	else if (inst_code == 13)
		return ("lld");
	else
		return ("lldi");
}

static void	print_instruction(t_car *car, t_inst instruct, unsigned char *arena)
{
	int	inst;
	int	arg_count;
	int	arg;

	inst = instruct.inst_code;
	arg_count = get_arg_count(inst);
	arg = 1;
	ft_printf("Process %d: %s ", car->id, get_inst_name(inst));
	while (arg <= arg_count)
	{
		if (instruct.types[arg - 1] == IND_CODE && inst != 13)
			ft_printf("%hd ", get_ind_val(instruct, arena, car, arg) % IDX_MOD);
		else if (instruct.types[arg - 1] == IND_CODE && inst == 13)
			ft_printf("%hd ", get_ind_val(instruct, arena, car, arg));
		else
			ft_printf("%d ", get_arg_val(instruct, arena, car, arg));
		arg++;
	}
	if (inst != 1 && inst != 9 && inst != 12 && inst != 15)
		print_arg_types(arena, car, instruct);
	ft_putchar('\n');
}

/*
** prints various events happening during the execution of the program.
** @verb can be 1 or 2, indicating either an instruction execution attempt or
** carriage death (respectively).
*/
void	print_verbose(t_car *car,
		t_inst instruct,
		unsigned char *arena,
		int verb
		)
{
	if (verb == 1)
		print_instruction(car, instruct, arena);
	else
		ft_printf("Process %d died\n", car->id);
}
