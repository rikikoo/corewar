/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:46:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/27 18:23:44 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"

typedef struct s_statement {
	char	*label;
	int		statement_code;
	char	*argv[3];

}	t_statement;

typedef struct s_data{
	int			source_fd;
	int			target_fd;
	char		*filename;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	u_int32_t	champ_size;
	int			row;
	int			col;
}	t_data;

// core
void		assemble(char *filename);
t_data		*init_data(char *filename);

// utils
void		usage(void);
void		error_exit(char *s);
void		parser_error_exit(char *s, int row, int col);
void		*malloc_safe(size_t size);
void		free_data(t_data *data);

// read functions
void		read_file(t_data *data);
void		skip_whitespace(char *s, size_t *i);

// write functions
void		write_file(t_data *data);
void		write_header(t_data *data);
void		write_magic_header(int fd);
void		write_champion_name(t_data *data);
void		write_champion_comment(t_data *data);
void		write_null(int fd);
void		write_exec_size(t_data *data);

// write utils
u_int32_t	u_int_32_to_big_endian(u_int32_t n);
#endif