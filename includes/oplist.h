/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:20:25 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/06 13:30:30 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPLIST_H
# define OPLIST_H
# include "op.h"

typedef struct s_oplist
{
	u_int8_t	op_code;
	char		*op_name;
	int			arg_cnt;
	int			arg_type[3];
	int			t_dir_size;
	int			arg_type_code;
}	t_oplist;

static const t_oplist	g_oplist[16] = {
{
	.op_code = 0x01,
	.op_name = "live",
	.arg_cnt = 1,
	.arg_type = {T_DIR, 0, 0},
	.t_dir_size = 4,
	.arg_type_code = 0
},
{
	.op_code = 0x02,
	.op_name = "ld",
	.arg_cnt = 2,
	.arg_type = {T_DIR | T_IND, T_REG, 0},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x03,
	.op_name = "st",
	.arg_cnt = 2,
	.arg_type = {T_REG, T_IND | T_REG, 0},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x04,
	.op_name = "add",
	.arg_cnt = 3,
	.arg_type = {T_REG, T_REG, T_REG},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x05,
	.op_name = "sub",
	.arg_cnt = 3,
	.arg_type = {T_REG, T_REG, T_REG},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x06,
	.op_name = "and",
	.arg_cnt = 3,
	.arg_type = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x07,
	.op_name = "or",
	.arg_cnt = 3,
	.arg_type = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x08,
	.op_name = "xor",
	.arg_cnt = 3,
	.arg_type = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x09,
	.op_name = "zjmp",
	.arg_cnt = 1,
	.arg_type = {T_DIR, 0, 0},
	.t_dir_size = 2,
	.arg_type_code = 0
},
{
	.op_code = 0x0a,
	.op_name = "ldi",
	.arg_cnt = 3,
	.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	.t_dir_size = 2,
	.arg_type_code = 1
},
{
	.op_code = 0x0b,
	.op_name = "sti",
	.arg_cnt = 3,
	.arg_type = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
	.t_dir_size = 2,
	.arg_type_code = 1
},
{
	.op_code = 0x0c,
	.op_name = "fork",
	.arg_cnt = 1,
	.arg_type = {T_DIR, 0, 0},
	.t_dir_size = 2,
	.arg_type_code = 0
},
{
	.op_code = 0x0d,
	.op_name = "lld",
	.arg_cnt = 2,
	.arg_type = {T_DIR | T_IND, T_REG},
	.t_dir_size = 4,
	.arg_type_code = 1
},
{
	.op_code = 0x0e,
	.op_name = "lldi",
	.arg_cnt = 3,
	.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	.t_dir_size = 2,
	.arg_type_code = 1
},
{
	.op_code = 0x0f,
	.op_name = "lfork",
	.arg_cnt = 1,
	.arg_type = {T_DIR, 0, 0},
	.t_dir_size = 2,
	.arg_type_code = 0
},
{
	.op_code = 0x10,
	.op_name = "aff",
	.arg_cnt = 1,
	.arg_type = {T_REG, 0, 0},
	.t_dir_size = 4,
	.arg_type_code = 1
}
};

#endif