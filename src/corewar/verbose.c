/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:41:28 by rkyttala          #+#    #+#             */
/*   Updated: 2022/08/31 23:08:08 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_arg_types(unsigned char *arena, t_car *car, t_inst inst)
{
	int	i;
	int	ic;

	ic = inst.inst_code;
	if (ic == 1 || ic == 9 || ic == 12 || ic == 15)
		return ;
	i = 0;
	ft_printf("(ACB: %#2x", arena[(car->pos + 1) % MEM_SIZE]);
	ft_printf(" [ ");
	while (inst.types[i] && i < 4)
	{
		ft_printf("%d ", inst.types[i]);
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

static void	ind_print(
			unsigned char *arena,
			t_inst inst,
			t_car *car,
			int arg
			)
{
	int		d;
	short	hd;

	hd = get_ind_val(inst, arena, car, arg);
	d = bytes_to_int(arena, rel_pos(car->pos, hd), DIR_SIZE);
	if (inst.inst_code == 2)
		ft_printf("%d ", d);
	else if (inst.inst_code == 13)
		ft_printf("%hd ", hd);
	else
		ft_printf("%hd ", hd % IDX_MOD);
}

void	print_instruction(t_car *car, t_inst inst, unsigned char *arena)
{
	int		arg_count;
	int		arg;

	arg_count = get_arg_count(inst.inst_code);
	arg = 0;
	ft_printf("Process %d : %s ", car->id, get_inst_name(inst.inst_code));
	while (++arg <= arg_count)
	{
		if (inst.sizes[arg - 1] == IND_SIZE)
			ind_print(arena, inst, car, arg);
		else
		{
			if (inst.types[arg - 1] == REG_CODE)
				ft_printf("r%d:", get_reg_no(inst, arena, car->pos, arg));
			ft_printf("%d ", get_arg_val(inst, arena, car, arg));
		}
	}
	print_arg_types(arena, car, inst);
	ft_putchar('\n');
}
