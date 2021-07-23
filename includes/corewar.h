/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:55:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/23 19:36:53 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4

/*
** MEM_SIZE			MAX_PLAYERS * 1024
** IDX_MOD			MEM_SIZE / 8
** CHAMP_MAX_SIZE	MEM_SIZE / 6
*/
# define MEM_SIZE			4096
# define IDX_MOD			512
# define CHAMP_MAX_SIZE		682

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048
# define COREWAR_EXEC_MAGIC	0xea83f3

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

typedef struct s_core
{
	unsigned int	aff;
	unsigned int	dump;
	unsigned int	split;
	unsigned int	verbose;
	unsigned int	champ_count;
	unsigned int	player_number;
	unsigned int	carry;
	unsigned int	*program_counter;
}	t_core;

typedef struct s_champs
{
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned int	magic;
	unsigned char	size;
	char			bytes[CHAMP_MAX_SIZE];
	struct s_champs	*next;
}	t_champs;

void		print_usage(void);
void		print_error(const char *message, const char *filepath);
t_champs	*parse_args(const int argc, char **argv, t_core *core);
t_champs	*read_cor(const char *filepath, t_core *core);

#endif
