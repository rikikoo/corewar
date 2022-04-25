/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:46:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/25 16:42:30 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"

typedef struct s_statement {
	char	**token;
}	t_statement;

typedef struct s_commands {
	char				*name;
	char				*comment;
	struct s_statement	**statements;
}	t_commands;

void		usage(void);
void		error_exit(char *s);
void		*malloc_safe(size_t size);
void		assemble(char *filename);
t_commands	*init_parser(int fd);
void		free_commands(t_commands *commands);
#endif