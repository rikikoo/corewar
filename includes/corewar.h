/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 22:55:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/21 23:16:24 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "op.h"

typedef struct	s_core
{
	int	aff;
	int	dump;
	int	split;
	int	verbose;
	int	champ_count;
	int	player_number;
}	t_core;

typedef struct	s_champs
{
	char			*name;
	char			*comment;
	struct s_champs	*next;
}	t_champs;

void		print_usage(void);
void		print_error(const char *message, const char *filepath);
t_champs	*parse_args(const int argc, char **argv, t_core *core);
t_champs	*read_cor(const char *filepath, t_core *core);

#endif
