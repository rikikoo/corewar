/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:46:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/26 18:57:51 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"

typedef struct s_statement {
	char	**token;
}	t_statement;

typedef struct s_data{
	int		source_fd;
	int		target_fd;
	char	*filename;
	char	*name;
	char	*comment;
	int		row;
	int		col;
}	t_data;

// utils
void		usage(void);
void		error_exit(char *s);
void		parser_error_exit(char *s, int row, int col);
void		*malloc_safe(size_t size);

// core functions
void		assemble(char *filename);
t_data		*init_data(char *filename);
void		read_file(t_data *data);
void		free_data(t_data *data);

// write functions
void		write_file(t_data *data);
void		write_header(t_data *data);
#endif