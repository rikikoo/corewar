/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:46:38 by vhallama          #+#    #+#             */
/*   Updated: 2022/09/25 18:01:17 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"

typedef struct s_label {
	char			*label;
	u_int32_t		pos;
	struct s_label	*next;
}	t_label;

typedef struct s_statement {
	struct s_label		*label;
	char				*op_name;
	u_int8_t			op_code;
	char				*arg[3];
	u_int8_t			argtypes[3];
	int					t_dir_size;
	int					arg_type_code;
	u_int32_t			pos;
	struct s_statement	*next;
}	t_statement;

typedef struct s_data{
	int			source_fd;
	int			target_fd;
	char		*filename;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	int			has_name;
	int			has_comment;
	u_int32_t	champ_size;
	size_t		row;
	size_t		col;
}	t_data;

// core
void		assemble(char *filename);
t_data		*init_data(char *filename);
t_statement	*init_list(void);

// utils
void		usage(void);
void		error_exit(char *s);
void		parser_error_exit(char *s, int row, int col);
void		*malloc_safe(size_t size);
void		append_labels(t_label **head);
void		append_list(t_statement **head);

// cleanup
void		free_data(t_data *data);
void		free_list(t_statement **head);

// read functions
void		read_file(t_data *data, t_statement *cur, char *line, int type);
void		check_for_newline_at_the_end_of_file(t_data *data);

// read utils
void		skip_whitespace(char *s, size_t *i);
void		null_comment(char *s);

// tokenization
void		tokenize_line(t_data *data, t_statement *cur, char *s);

void		get_t_reg_arg(t_data *data, t_statement *cur, int arg_num, char *s);
void		get_t_dir_arg(t_data *data, t_statement *cur, int arg_num, char *s);
void		get_t_ind_arg(t_data *data, t_statement *cur, int arg_num, char *s);

// tokenization utils
int			is_label_char(char s);
void		save_label(char *label, t_statement *cur, int cur_size);
void		assign_op_specs(t_data *data, t_statement *st);

// tokenization validation
void		validate_arg_amount(t_data *data, t_statement *cur);
void		validate_arg_type(t_data *data, t_statement *cur, int arg_num,
				int arg_type);
void		validate_arg_end(t_data *data, char *s);

// validation
void		validate_labels(t_statement *list);

// write functions
void		write_file(t_data *data, t_statement *st);

// write header
void		write_magic_header(int fd);
void		write_champion_name(t_data *data);
void		write_champion_comment(t_data *data);
void		write_null(int fd);
void		write_exec_size(t_data *data);

// write exec code
void		write_statement_code(t_statement *st, int fd);
void		write_argument_type_code(t_statement *st, int fd);
void		write_arguments(t_statement **head, t_statement *st, int fd);

// write utils
u_int16_t	u_int16_to_big_endian(u_int16_t n);
u_int32_t	u_int32_to_big_endian(u_int32_t n);
u_int32_t	find_label_pos(t_statement **head, char *match);

#endif