/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:55:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/02 10:46:21 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** statement argument definitions
*/
# define MAX_ARGS_NUMBER	4
# define IDX_MOD			512

# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE
# define IND_SIZE			2

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define REG_NUMBER			16
# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

/*
** assembly character definitions
*/
# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','
# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

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
** Game rules/parameters
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
	int	aff;
	int	dump;
	int	split;
	int	verbose;
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
	int				cycles_to_die;
	int				checks;
	int				winner;
	struct s_champ	*last_live_report;
	struct s_car	*cars;
}	t_game;

typedef struct s_car
{
	int				id;
	int				pos;
	int				carry;
	int				cycles_since_live;
	int				cycles_to_exec;
	int				next_instruction;
	int				registry[REG_NUMBER];
	unsigned char	current_opcode;
	struct s_car	*next;
}	t_car;

void	parse_args(int ac, char **av, t_flags *flags, t_champ *champs);
t_champ	read_cor(const char *filepath, t_flags *flags);
void	sort_champs(t_champ *champs, int champ_count);
size_t	n_bytes_toint(const unsigned char *bytes, int n);
int		get_arg_type(unsigned char byte, int arg);
void	print_usage(void);
void	print_error(int errno, const char *path, t_champ *champ);
void	init_arena(t_champ *champs, int champ_count, unsigned char *arena);
t_car	*new_car(int prev_id, int pos, int playernbr);
t_game	init_game(t_champ *champ, t_car *car);
int		start_game(t_flags flags, t_champ *champs, unsigned char *arena);
int		start_cycles(t_flags flags, t_champ *champs, unsigned char *arena, \
		t_game *game);
int		arithmetic_inst(int inst, t_car *car, unsigned char *arena);
int		bitwise_inst(int inst, t_car *car, unsigned char *arena);
int		get_arg_type(unsigned char byte, int arg);

#endif
