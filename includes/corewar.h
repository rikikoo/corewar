/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:55:18 by rkyttala          #+#    #+#             */
/*   Updated: 2022/10/06 22:52:31 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** statement argument definitions
*/
# define MAX_ARGS_NUMBER	4
# define REG_NUMBER			16
# define IDX_MOD			512

# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE
# define IND_SIZE			2

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

/*
** champion-related info & size restrictions
*/
# define COREWAR_EXEC_MAGIC	0xea83f3
# define MAX_PLAYERS		4
# define MEM_SIZE			4096
# define CHAMP_MAX_SIZE		682
# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048

/*
** game rules/parameters
*/
# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

typedef struct s_flags
{
	int	dump;
	int	verbose;
	int	row_len;
	int	champ_count;
	int	used_nbrs[MAX_PLAYERS];
	int	playernbr;
}	t_flags;

typedef struct s_champ
{
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	exec[CHAMP_MAX_SIZE];
	unsigned int	magic;
	int				playernbr;
	int				size;
}	t_champ;

typedef struct s_game
{
	int				cycle;
	int				lives;
	int				cycle_to_die;
	int				next_check;
	int				checks;
	int				winner;
	int				live_count;
	int				latest_car_id;
	int				last_live_report;
	int				champ_count;
	struct s_car	*cars;
	struct s_flags	flags;
}	t_game;

typedef struct s_car
{
	int				id;
	int				pos;
	int				carry;
	int				last_live;
	int				cycles_to_exec;
	int				registry[REG_NUMBER];
	unsigned char	current_opcode;
	struct s_car	*next;
}	t_car;

typedef struct s_inst
{
	int	inst_code;
	int	is_valid;
	int	types[MAX_ARGS_NUMBER];
	int	sizes[MAX_ARGS_NUMBER];
}	t_inst;

/*
** PARSE INPUT
*/
void	parse_args(int ac, char **av, t_flags *flags, t_champ *champs);
t_champ	read_cor(const char *filepath, t_flags *flags);
void	sort_champs(t_champ *champs, t_flags *flags);

/*
** GAME MAIN LOOP
*/
t_car	*new_car(int prev_id, int pos, int playernbr);
int		start_game(t_flags flags, unsigned char *arena, t_champ *champs);
int		start_cycles(unsigned char *arena, t_game *game, t_champ *champs);
int		perform_check(t_game *game, t_car *prev, t_car *next, int alive);

/*
** INSTRUCTIONS
*/
int		stay_alive(t_game *game, t_car *car, unsigned char *arena, \
		t_champ *champs);
int		load_inst(int inst_code, t_game *game, t_car *car, \
		unsigned char *arena);
int		store_inst(t_game *game, t_car *car, unsigned char *arena);
int		arithmetic_inst(int inst_code, t_game *game, t_car *car, \
		unsigned char *arena);
int		bitwise_inst(int inst_code, t_game *game, t_car *car, \
		unsigned char *arena);
int		jump_inst(t_game *game, t_car *car, unsigned char *arena);
int		ind_load_inst(int inst_code, t_game *game, t_car *car, \
		unsigned char *arena);
int		ind_store_inst(t_game *game, t_car *car, unsigned char *arena);
int		fork_inst(int inst_code, t_game *game, t_car *car, \
		unsigned char *arena);
int		longload_inst(int inst_code, t_game *game, t_car *car, \
		unsigned char *arena);
int		print_aff(t_car *car, unsigned char *arena);

/*
** VALIDATION
*/
t_inst	validate_instruction(int inst_code, unsigned char *arena, int pos);
int		get_arg_count(int inst_code);
int		get_arg_type(unsigned char byte, int arg);
int		get_arg_size(int inst_code, int arg);
int		get_arg_val(t_inst inst, unsigned char *arena, t_car *car, int arg);
int		get_reg_no(t_inst inst, unsigned char *arena, int pos, int arg);
short	get_ind_val(t_inst inst, unsigned char *arena, t_car *car, int arg);
void	get_inst_operands(t_inst inst, unsigned char *arena, t_car *car, \
		int *vals);

/*
** UTILS
*/
int		bytes_to_int(const unsigned char *arena, int pos, int n);
int		rel_pos(int car_pos, int relative_pos);
void	swap_endianness(unsigned char *bytes, int len);
void	write_to_arena(unsigned char *arena, unsigned char *src, int start, \
		int len);
void	print_usage(void);
void	print_error(int errno, const char *path, t_champ *champ);
void	print_live(t_champ champ);
void	print_cars(t_game *game);
void	print_instruction(t_car *car, t_inst inst, unsigned char *arena);
void	dump_memory(const unsigned char *arena, int row_len);

#endif
