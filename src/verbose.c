/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:41:28 by rkyttala          #+#    #+#             */
/*   Updated: 2022/05/22 15:55:16 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_arg_types(unsigned char *arena, t_car *car, t_inst instruct)
{
	int	i;

	i = 0;
	ft_printf("Argument coding byte: %#2x", arena[(car->pos + 1) % MEM_SIZE]);
	ft_printf(" ( ");
	while (instruct.types[i] && i < 4)
	{
		ft_printf("%d ", instruct.types[i]);
		i++;
	}
	ft_printf(")");
	ft_putchar('\n');
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

	inst = instruct.inst_code;
	arg_count = get_arg_count(inst);
	if (arg_count == 1)
		ft_printf("Player %d: %s %d\n", \
		car->registry[0] * -1, get_inst_name(inst), \
		n_bytes_to_int(arena, (car->pos + 1) % MEM_SIZE, IND_SIZE));
	else if (arg_count == 2)
		ft_printf("Player %d: %s %d %d\n", \
		car->registry[0] * -1, get_inst_name(inst), \
		get_arg_value(instruct, arena, car, 1), \
		get_arg_value(instruct, arena, car, 2));
	else
		ft_printf("Player %d: %s %d %d %d\n", \
		car->registry[0] * -1, get_inst_name(inst), \
		get_arg_value(instruct, arena, car, 1), \
		get_arg_value(instruct, arena, car, 2), \
		get_arg_value(instruct, arena, car, 3));
	ft_printf("\n");
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
	{
		// debug start
		if (instruct.inst_code != 1 && instruct.inst_code != 9 && \
		instruct.inst_code != 13 && instruct.inst_code != 15)
			print_arg_types(arena, car, instruct);
		// debug end
		print_instruction(car, instruct, arena);
	}
	else
		ft_printf("Program Counter %d (of player number %d) died\n", \
		car->id, car->registry[0] * -1);
}
